# StudentManagement
college project

i tried.
=================================================================================================================================
اول که از دو تا استراکت درست کردیم برای درس ها و اطلاعات دانشجو.8-24

struct Course {
    string name;
    int credits;
    float grade;
};

struct Student {
    string firstName, lastName;
    string studentID;
    string major;
    vector<Course> courses;
    float gpa;
};
=================================================================================================================================

بعد از وکتور استفاده کردیم چون حذف و اضافه خیلی باهاش راحت تره تا اینکه ارایه بزرگ بدیم و هی دستکاریش کنیم 26

vector<Student> students;

=================================================================================================================================
تعریف تابع ها 28-37

تابع اصلی هست که با دستور do while مجبور میکنیم که حتما یکبار ااین حلقه اجرا شه و کاربر بتونه تصمیم بگیره... 8 تا گزینه قرار دادیم:ثبت دانشجو، اضافه کردن درس(اینجا کاربر دو اپشن میگیره که اضافه کنه یا ادیت کنه)، لیست دانشجو، کارنامه، حذف دانشجو، جست و جوی داشنجو با کد دانشجویی، ادیت اطلاعات دانشجو، خروج 
یه سوییچ ساده اول استفاده کردیم که مشکل این بود وقتی کاربر دکمه رندوم (مثلا کنترل) رو میزد یک حلقه بی نهایت تشکیل میشد بخاطر همین یک شرط استفادده کردیم که چک کنه اگه کاربر کلید رندوم زد اون رو پاک کنه و دوباره ریستارت شه برنامه. بعد تویه سوییچ هم که توضیح نداره اصا.40-83
int main() {
    int choice;
    do {
        cout << "\n1. Register Student\n2. Add Course\n3. List Students\n4. Print Transcript\n5. Delete Student\n6. Search Student\n7. Edit student Info\n8. Exit\n\nOption: ";
        
        if (!(cin >> choice)) { 
            cin.clear();  // پاک کردن خطای ورودی
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // حذف ورودی نامعتبر
            cout << "\nInvalid input! Please select an option.\n";
            continue;
        }

        switch (choice) {
            case 1: registerStudent(); break;
            case 2: addCourse(); break;
            case 3: {
                string major;
                cout << "\nEnter major to filter (or press enter to list all): ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, major);
                listStudents(major);
                break;
            }
            case 4: printTranscript(); break;
            case 5: deleteStudent(); break;
            case 6: searchStudent(); break;
            case 7: editStudentInfo(); break;
            case 8: cout << "\nExiting...\n"; break;
            default: cout << "\nInvalid option!\n";
        }
    } while (choice != 8);
    return 0;
}
=================================================================================================================================

تابع اول تابع ثبت دانشجو registerStudent عه که void هست توش یه استودنت از استراکتمون متغییر تعریف میکنیم s و بعد اطالاعات رو ثبت میکنیم دیگه با . به اعضای استراکت دسترسی پیدا میکنیم دیگه این که مشخصه. که این دو بار اصلاح شد بار اول مشکل این بود که وقتی کاربر اینتر میزد new line خونده میشد و کامند بعدی باگ میخورد و اصا رد میشد که یه .ignore گذاشتم اوکی شد 87-108

int main() {
    int choice;
    do {
        cout << "\n1. Register Student\n2. Add Course\n3. List Students\n4. Print Transcript\n5. Delete Student\n6. Search Student\n7. Edit student Info\n8. Exit\n\nOption: ";
        
        if (!(cin >> choice)) { 
            cin.clear();  // پاک کردن خطای ورودی
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // حذف ورودی نامعتبر
            cout << "\nInvalid input! Please select an option.\n";
            continue;
        }

        switch (choice) {
            case 1: registerStudent(); break;
            case 2: addCourse(); break;
            case 3: {
                string major;
                cout << "\nEnter major to filter (or press enter to list all): ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, major);
                listStudents(major);
                break;
            }
            case 4: printTranscript(); break;
            case 5: deleteStudent(); break;
            case 6: searchStudent(); break;
            case 7: editStudentInfo(); break;
            case 8: cout << "\nExiting...\n"; break;
            default: cout << "\nInvalid option!\n";
        }
    } while (choice != 8);
    return 0;
}

=================================================================================================================================

 تابع بعدی addCourse که درس اضافه میکنه هم دو بار اپدیت شد بار اول باگ هایی وجود داشت بخاطر همین new line که دوباره مثل تابع قبلی .ignore زدیم و getline چون 
ممکن بود فاصله باشه. بار دوم اپدیت برای اضافه کردن اپشن ادیت و حذف دروس بود که اضافه شد که در اخریش دو انتخاب اضافه کردن هست (شرط) و ادیت که برای ادیت هم باز هر برا برنامه از کاربر میپرسه که میخان چه اطلاعاتی رو ادیت کنن و چیا رو نگه دارن مثلا برای نگه داشتن یه اطلاعاتی میتونن -1 بزنن که تغییر نکنه

void addCourse() {
    string id;
    cout << "Enter student ID: "; cin >> id;
    for (auto &s : students) {
        if (s.studentID == id) {
            int choice;
            do {
                cout << "\n1. Add New Course\n2. Edit Existing Course\n3. Delete Course\n4. Go Back\nOption: ";
                while (!(cin >> choice) || choice < 1 || choice > 4) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input! Please enter a number between 1 and 4: ";
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (choice == 1) { // اضافه کردن درس جدید
                    Course c;
                    cout << "\nEnter course name: "; getline(cin, c.name);
                    cout << "Enter credits: "; cin >> c.credits;
                    cout << "Enter grade: "; cin >> c.grade;
                    s.courses.push_back(c);
                } 
                else if (choice == 2) { // ویرایش درس موجود
                    // کد ویرایش درس
                } 
                else if (choice == 3) { // حذف درس
                    // کد حذف درس
                }

                // به‌روزرسانی معدل
                float totalGrade = 0, totalCredits = 0;
                for (auto &course : s.courses) {
                    totalGrade += course.grade * course.credits;
                    totalCredits += course.credits;
                }
                s.gpa = (totalCredits > 0) ? (totalGrade / totalCredits) : 0;

            } while (choice != 4);
            return;
        }
    }
    cout << "Student not found!\n";
}
=================================================================================================================================

این تابع لیست دانشجوها رو نمایش می‌ده. کاربر می‌تونه بر اساس رشته فیلتر کنه و دانشجوها بر اساس معدل مرتب می‌شن.که در ابتدا باید چک کرد وکتورمون خالیه یا نه اگه خالی بود که مینویسه اگه نبود میاد و نمایش میده که این تابع از اسون ترین تابع ها بود. تنها جای چیزش این بود که اگر کاربر بخواد لیست رو بر اساس رشته فیلتر کنه باید یه وکتور جدید میزاشتیم و چک میکردیم که ایا اعضایه وکتور اصلیمون این ویژگی رشته رو در خودشون داشتن یا نه که یه شرط سادس و اگر این شرط برقرار بود به وکتور جدید (فیلتر شده اضافه میشه)

void listStudents(string majorFilter = "") {

        //update this will still search if  student is empty so i had to change/check
        if (students.empty()) {
        cout << "No students available!\n";
        return;
        }   

        vector<Student> filteredStudents;
        for (const auto &s : students) {
            if (majorFilter.empty() || s.major == majorFilter) {
                filteredStudents.push_back(s);
            }
        }

        sort(filteredStudents.begin(), filteredStudents.end(), [](const Student &a, const Student &b) {
            return a.gpa > b.gpa;
        });

        for (const auto &s : filteredStudents) {
            cout << s.firstName << " " << s.lastName << " | " << s.studentID << " | " << s.major << " | GPA: " << s.gpa << endl;
        }
    }

=================================================================================================================================

    تابع بعدی تابع جاپ کارنامس که بر عکس تابع ثبت کارنامس دیگه یه cout ساده از ممبر وکتورمونه یه شرط اولش گذاشتیم که بره و چک کنه کدوم ممبر وکتورمون کد دانشجوییش با خواسته کاربر یکیه که اطلاعات رو چاپ کنه.
    void printTranscript() {

        string id;
        cout << "Enter student ID: \n"; cin >> id;

        for (const auto &s : students) {

            if (s.studentID == id) {
                cout << "****~Transcript~****\n";
                cout << "Name: " << s.firstName << " " << s.lastName << "\n";
                cout << "Student ID: " << s.studentID << "\n";
                cout << "Major: " << s.major << "\n";
                cout << "GPA: " << s.gpa << "\n\n";
                cout << "Courses: \n";

                for (const auto &c : s.courses) {
                    cout << "- " << c.name << " (" << c.credits << " credits) | Grade: " << c.grade << "\n";
                }
                return;
            }
        }
        cout << "Student not found!\n";
    }
    ============================================================================================================================

    تابع بعدی deleteStudent هست که مشخصه از اسم برای حذف کل اطلاعات دانشجو از وکتوره که من فانکشنش رو از یوتیوب پیدا کردم

    void deleteStudent() {
        string id;
        cout << "Enter student ID to delete: "; cin >> id;

        auto it = remove_if(students.begin(), students.end(), [&](const Student &s) {
            return s.studentID == id;
        });

        if (it != students.end()) {
            students.erase(it, students.end());
            cout << "Student deleted successfully!\n";
        } else {
            cout << "Student not found!\n";
        }
    }

=================================================================================================================================

تابع بعدی تابع سرچ هست searchStudent  که مشخصه با دریافت کد دانشجویی از کاربر میاد و بررسی میکنه که همچین کد دانشجویی توی وکتور دانشجو ها وجود داره یا نه بعدم که اطلاعات رو مثل کارنامه چاپ میکنه اگر پیدا نشد که چاپ میکنه پیدا نشد دیگه
void searchStudent() {
    string query;
    cout << "\nEnter student name or ID to search: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    getline(cin, query);

    bool found = false;
    for (const auto &s : students) {
        if (s.firstName == query || s.lastName == query || s.studentID == query) {
            cout << "\nStudent Found:\n";
            cout << "Name: " << s.firstName << " " << s.lastName << "\n";
            cout << "Student ID: " << s.studentID << "\n";
            cout << "Major: " << s.major << "\n";
            cout << "GPA: " << s.gpa << "\n";
            cout << "Courses: \n";
            for (const auto &c : s.courses) {
                cout << "- " << c.name << " (" << c.credits << " credits) | Grade: " << c.grade << "\n";
            }
            found = true;
        }
    }
    if (!found) {
        cout << "No matching student found!\n";
    }
}

=================================================================================================================================

یه تابع جدید اخر سر اضافه کردیم برای ادیت اطلاعات دانشجو که مثل ادیت درس ها عمل میکنه دونه به دونه میپرسه از کاربر که میخاد این قسمت از اطلاعات رو تغییر بده یا نه این قسمت (کلا همه قسمتا) هم با کد داشنجویی کار میکنه میشد اپشن های دیگه اضافه کرد ولی خب نخواستید ننوشتم
void editStudentInfo() {
    string id;
    cout << "Enter student ID to edit: "; cin >> id;
    for (int i = 0; i < students.size(); i++) {
        if (students[i].studentID == id) {
            cout << "Editing Student: " << students[i].firstName << " " << students[i].lastName << "\n";
            string input;
            cout << "Enter new first name (or press Enter to keep the same): ";
            cin.ignore();
            getline(cin, input);
            if (input != "") {
                students[i].firstName = input;
            }
            // بقیه فیلدها هم به همین شکل ویرایش می‌شن
            cout << "Student info updated!\n";
            return;
        }
    }
    cout << "Student not found!\n";
}

=================================================================================================================================

پایان.
تهیه کنندگان: سمانه میرزایی و پونه صادقیک.
