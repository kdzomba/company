#ifndef COMPANY_H_INCLUDED
#define COMPANY_H_INCLUDED

class Employee;
class TeamLeader;
class Project;
using ShrEmployee = std::shared_ptr<Employee>;
using ShrLeader = std::shared_ptr<TeamLeader>;

/**Company**/
class Company {

     public:
        using real = double;
        Company(real hiringCost);
        void LoadEmployees(std::string fileName);
        void SaveEmployees(std::string fileName);
        void Hire(std::string code, char category, real salary, real bonus);
        void CreateProject(std::string projectName, int engineersCnt, int testerCnt);
        void DisplayTeam(std::string projectName);
        double GetProjectCost(std::string projectName, int duration);
        void FinishProject(std::string projectName, int duration);
     private:
        double hCost;
        std::vector<ShrEmployee> employees;
        std::vector<Project> projects;
};

#endif
