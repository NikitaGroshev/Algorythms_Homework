#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cmath>


const double pi = std::acos(-1.0);


std::vector<int> topological_sort(const std::vector<std::vector<int>> &g)
{
    std::vector<bool> visited(g.size());
    std::vector<int> sorted;
    std::function<void(int)> dfs = [&](int v)
    {
        visited[v] = true;
        for(int u : g[v])
            if(!visited[u])
                dfs(u);
        sorted.push_back(v);
    };
    for (size_t v = 0; v < g.size() ; ++v)
        if(!visited[v])
            dfs(v);
    std::reverse(sorted.begin(),sorted.end());
    return sorted;
}


class Vertex {
    int vertex_id = 0;

    public:
        virtual ~Vertex() {};
        virtual unsigned num_inputs() const = 0; 
        virtual void set_input(int inp_idx,double inp_val) = 0; 
        virtual unsigned num_outputs() const = 0; 
        virtual double get_output(int out_idx) = 0; 
        virtual void calc_value() = 0; 
}; 


struct Edge 
{ 
    unsigned out_vertex_id; 
    unsigned out_port_id; 
    unsigned inp_vertex_id; 
    unsigned inp_port_id; 
};


class CalcGraph : public Vertex 
{ 
    std::vector<Vertex*> vertices = {};
    std::vector<Edge> edges = {};
    std::vector<std::vector<int>> graph = {{}};
    std::vector<double> out_values = {};
    std::vector<double> inp_values = {};
    std::vector<int> operation_order = {};

    void create_graph() {
        graph.resize(vertices.size());
        for (const auto edge : edges) {
            graph[edge.out_vertex_id].push_back(edge.inp_vertex_id);
        }
    }

    void create_inp_values() {
        for (size_t i = 0; i < vertices.size(); i++) {
            for (size_t j = 0; j < vertices[i]->num_inputs(); j++) {
                bool has_input = false;
                for (auto edge: edges) {
                    if (edge.inp_vertex_id == i && edge.inp_port_id == j) {
                        has_input = true;
                        break;
                    }
                }
                if (!has_input) {
                    inp_values.push_back(0.0);
                }
            }
        }
    }

    void create_out_values() {
        for (size_t i = 0; i < vertices.size(); i++) {
            for (size_t j = 0; j < vertices[i]->num_outputs(); j++) {
                bool has_output = false;
                for (auto edge: edges) {
                    if (edge.out_vertex_id == i && edge.out_port_id == j) {
                        has_output = true;
                        break;
                    }
                }
                if (!has_output) {
                    out_values.push_back(0.0);
                }
            }
        }
    }

    public:
        ~CalcGraph() {
            for (auto v: vertices) {
                delete v;
            }
        }

        unsigned num_inputs() const override {
            return inp_values.size();
        };

        unsigned num_outputs() const override {
            return out_values.size();
        };

        void set_input(int inp_idx, double inp_val) override {
            if (inp_idx > num_inputs() || inp_idx < 0) {
                throw std::out_of_range("Bad inp_idx in the CalcGraph::set_input");
            }
            inp_values[inp_idx] = inp_val;
        };
  
        double get_output(int out_idx) override {
            return out_values[out_idx];
        };

        void calc_value() override {
            int inp_counter = 0;

            for (size_t i = 0; i < vertices.size(); i++) {
                for (size_t j = 0; j < vertices[i]->num_inputs(); j++) {
                    bool has_input = false;
                    for (auto edge: edges) {
                        if (edge.inp_vertex_id == i && edge.inp_port_id == j) {
                            has_input = true;
                            break;
                        }
                    }
                    if (!has_input) {
                        vertices[i]->set_input(j, inp_values[inp_counter++]);
                    }
                }
            }

            for (int v: operation_order) {
                for (size_t i = 0; i < vertices[v]->num_inputs(); i++) {
                    for (auto edge: edges) {
                        if (edge.inp_vertex_id == v && edge.inp_port_id == i) {
                            double res = vertices[edge.out_vertex_id]->get_output(edge.out_port_id);
                            vertices[v]->set_input(i, res);
                        }
                    }
                }

                vertices[v]->calc_value(); 
            }

            int out_counter = 0;
            for (size_t i = 0; i < vertices.size(); i++) {
                for (size_t j = 0; j < vertices[i]->num_outputs(); j++) {
                    bool has_output = false;
                    for (auto edge: edges) {
                        if (edge.out_vertex_id == i && edge.out_port_id == j) {
                            has_output = true;
                            break;
                        }
                    }
                    if (!has_output) {
                        out_values[out_counter++] = vertices[i]->get_output(j);
                    }
                }
            }
        }

        void set_data(
            const std::vector<Vertex*> &new_vertex, 
            const std::vector<Edge> &new_edges
        ) {
            vertices = new_vertex;
            edges = new_edges;
            create_graph();
            create_inp_values();
            create_out_values();
            operation_order = topological_sort(graph);
        };
};



class PlusOperator : public Vertex 
{ 
    double m_inp_val[2] = {0}; 
    double m_out_val = 0; 

    public: 
        unsigned num_inputs() const override { 
            return 2; 
        }

        void set_input(int inp_idx, double inp_val) override { 
            if (inp_idx < 0 || inp_idx >= 2) 
                throw std::out_of_range("Bad inp_idx in the PlusOperator::set_input"); 
            m_inp_val[inp_idx] = inp_val;
        }

        void calc_value() override { 
            m_out_val = m_inp_val[0] + m_inp_val[1]; 
        }

        unsigned num_outputs() const override { 
            return 1;
        }

        double get_output(int out_idx) override { 
            return m_out_val; 
        }
};


class ProductOperator : public Vertex
{
    double m_inp_val[2] = {0}; 
    double m_out_val = 0; 

    public: 
        unsigned num_inputs() const override { 
            return 2; 
        }

        void set_input(int inp_idx, double inp_val) override { 
            if (inp_idx < 0 || inp_idx >= 2) 
                throw std::out_of_range("Bad inp_idx in the ProductOperator::set_input"); 
            m_inp_val[inp_idx] = inp_val;
        }

        void calc_value() override { 
            m_out_val = m_inp_val[0] * m_inp_val[1]; 
        }

        unsigned num_outputs() const override { 
            return 1;
        }

        double get_output(int out_idx) override { 
            return m_out_val; 
        }   
};


class UnaryMinusOperator : public Vertex
{
    double m_inp_val = 0; 
    double m_out_val = 0; 

    public: 
        unsigned num_inputs() const override { 
            return 1; 
        }

        void set_input(int inp_idx, double inp_val) override { 
            m_inp_val = inp_val;
        }

        void calc_value() override { 
            m_out_val = -m_inp_val;
        }

        unsigned num_outputs() const override { 
            return 1;
        }

        double get_output(int out_idx) override { 
            return m_out_val; 
        }   
};


class SinusOperator : public Vertex
{
    double m_inp_val = 0; 
    double m_out_val = 0; 

    public: 
        unsigned num_inputs() const override { 
            return 1; 
        }

        void set_input(int inp_idx, double inp_val) override { 
            m_inp_val = inp_val;
        }

        void calc_value() override { 
            m_out_val = std::sin(m_inp_val);
        }

        unsigned num_outputs() const override { 
            return 1;
        }

        double get_output(int out_idx) override { 
            return m_out_val; 
        }   
};


class CosinusOperator : public Vertex
{
    double m_inp_val = 0; 
    double m_out_val = 0; 

    public: 
        unsigned num_inputs() const override { 
            return 1; 
        }

        void set_input(int inp_idx, double inp_val) override { 
            m_inp_val = inp_val;
        }

        void calc_value() override { 
            m_out_val = std::cos(m_inp_val);
        }

        unsigned num_outputs() const override { 
            return 1;
        }

        double get_output(int out_idx) override { 
            return m_out_val; 
        }   
};



int main() {

    // Пример: (cos(pi) + 3*sin(pi/2))*(10 + 5) = 30

    CalcGraph cg;
    std::vector< Vertex* > vertex; 
    std::vector< Edge > edges;

    vertex.push_back(new SinusOperator);   //vertex_id = 0 
    vertex.push_back(new ProductOperator); //vertex_id = 1 
    vertex.push_back(new CosinusOperator); //vertex_id = 2
    vertex.push_back(new PlusOperator);    //vertex_id = 3 
    vertex.push_back(new PlusOperator);    //vertex_id = 4 
    vertex.push_back(new ProductOperator); //vertex_id = 5

    edges.push_back(Edge{0, 0, 1, 0});
    edges.push_back(Edge{1, 0, 3, 0});
    edges.push_back(Edge{2, 0, 3, 1});
    edges.push_back(Edge{3, 0, 5, 0});
    edges.push_back(Edge{4, 0, 5, 1});

    cg.set_data(vertex,edges); 

    std::cout << "number of inputs: " << cg.num_inputs() << std::endl;
    std::cout << "number of outputs: " << cg.num_outputs() << std::endl;

    cg.set_input(0, pi / 2.0); 
    cg.set_input(1, 3.0);
    cg.set_input(2, pi); 
    cg.set_input(3, 10);
    cg.set_input(4, 5);

    cg.calc_value();

    std::cout << "result = " << cg.get_output(0) << std::endl; 
}