#include <iostream>
#include <vector>
#include <algorithm>


enum class DateType {
    birth = 1,
    death = -1,
    before_18 = 0
};

struct Date {
    int day;
    int month;
    int year;
    DateType t;
};

bool data_compare(const Date& date1, const Date& date2) {
    if (date1.year == date2.year) {
        if (date1.month == date2.month) {
            return date1.day < date2.day;
        }
        return date1.month < date2.month;
    }
    return date1.year < date2.year;
}

int main() {
    int N; std::cin >> N;
    std::vector<Date> dates_of_life;
    for (int i = 0; i < N; i++) {
        int d1; int m1; int y1;
        int d2; int m2; int y2;
        std::cin >> d1 >> m1 >> y1 >> d2 >> m2 >> y2;

        Date date_1 = {d1, m1, y1 + 18};                    // для проверки случая, когда исполнилось 18, но не исполнилось 19                                                        
        Date date_2 = {d2, m2, y2};                         // (и не умер в день рождения)

        if (y2 - y1 <= 18 && data_compare(date_2, date_1)) { 
            dates_of_life.push_back({d1, m1, y1 + 18, DateType::before_18});
            dates_of_life.push_back({d2, m2, y2, DateType::before_18});
        }
        else if (y2 - y1 < 80) {
            dates_of_life.push_back({d1, m1, y1 + 18, DateType::birth});
            dates_of_life.push_back({d2, m2, y2, DateType::death});
        } else if (y2 - y1 >= 80) {
            dates_of_life.push_back({d1, m1, y1 + 18, DateType::birth});
            dates_of_life.push_back({d2, m2, y2 - (y2 - y1 - 80), DateType::death});
        }
    }
    std::sort(dates_of_life.begin(), dates_of_life.end(), data_compare);

    int cur_amount = 0;
    int result = 0;

    for (int i = 0; i < dates_of_life.size(); i++) {
        if (dates_of_life[i].t == DateType::birth) {
            cur_amount += 1;
        }
        else if (dates_of_life[i].t == DateType::death) {
            cur_amount -= 1;
        }
        else if (dates_of_life[i].t == DateType::before_18) {
            continue;
        }
        result = std::max(result, cur_amount);
    }

    std::cout << result;
}