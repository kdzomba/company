#ifndef EMPLOYEE_H_INCLUDED
#define EMPLOYEE_H_INCLUDED

class Employee {

    public:
        using real = double;
        Employee(std::string cd, char cat, real sal) : code(cd), category(cat), salary(sal), inProject(false), needExtra(false) {}
        std::string getCode() { return code; }
        char getCategory() { return category; }
        real getSalary() { return salary; }
        bool getInProject() { return inProject;}
        void setInProject(bool z) { inProject = z; }
        bool getneedExtra() { return needExtra; }
        void setneedExtra(bool a) { needExtra = a; }
        virtual ~Employee() {}

    private:
        std::string code;
        char category;
        real salary;
        bool inProject;
        bool needExtra;

};

class TeamLeader : public Employee {

        public:
            TeamLeader(std::string cd, char cat, real sal, real bon) : Employee(cd, cat, sal), bonus(bon) {}
            real getBonus() { return bonus; }
            virtual ~TeamLeader() {}
        private:
            real bonus;

};
#endif
