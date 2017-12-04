#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include <memory>
#include <random>
#include "employee.h"
#include "company.h"
#include "project.h"


/**Constructor**/
Company::Company(real hiringCost) : hCost(hiringCost) {}

/**Load employees from a text file**/
void Company::LoadEmployees(std::string fileName) {

    std::ifstream myfile(fileName);
    std::string line;
    std::string code;
    char category;
    double salary;
    double bonus=0;

    if (myfile.is_open()) {

        while (getline (myfile,line)) {
            std::stringstream   ss(line);
            ss >> code >> category >> salary >>bonus;
            Hire(code, category, salary, bonus);
        }
        myfile.close();
        std::cout<<" Employees successfully added from a text file (if not in it)."<<std::endl<<std::endl;
    }
    else std::cout << "Can't open file"<<std::endl;

}

/**Save employees to a text file**/
void Company::SaveEmployees(std::string fileName) {

    std::ofstream myfile (fileName);

    if (myfile.is_open()) {

       std::vector<ShrEmployee>::iterator it;
       for(it = employees.begin(); it != employees.end(); ++it) {
            if((*it)->getCategory() == 'V') {
                 ShrLeader L = std::dynamic_pointer_cast<TeamLeader> (*it);
                 if(L!=nullptr)
                    myfile << L->getCode() << " " << L->getCategory() << " " << L->getSalary()<<" "<< L->getBonus()<<"\n";
            }
            else myfile << (*it)->getCode() << " " << (*it)->getCategory() << " " << (*it)->getSalary() << "\n";
        }
        myfile.close();
       }
       else std::cout << "Can't open file"<<std::endl;

       std::cout<<" Employees successfully saved to a text file."<<std::endl<<std::endl;
}



/**Hire new employee**/
void Company::Hire(std::string code, char category, real salary, real bonus ) {

    //provjera postoji li vec zaposlenik s zadanim kodom
    if(!employees.empty()) {
        std::vector<ShrEmployee>::iterator it;
        for(it = employees.begin(); it != employees.end(); ++it)
            if((*it)->getCode() == code) {
                 std::cout<<" Employee with given code already exists!"<<std::endl; return; }
    }

    //zaposli -> stavi u vektor svih zaposlenika
    try {

    if( category != 'V')
        employees.push_back(ShrEmployee (new Employee(code, category, salary)));
    else
       employees.push_back(ShrLeader (new TeamLeader(code, category, salary, bonus)));
     std::cout<<" Employee successfully added."<<std::endl;
     }
     catch(std::bad_alloc const & e) {
        std::cout << "Memory allocation error: " << e.what() << std::endl;
        std::exit(1);
     }

}


void inputNew(std::string &c, char &z, double &s, double &b);

/**Create new project**/
void Company::CreateProject(std::string projectName, int engineersCnt, int testerCnt) {

    Project newProject(projectName);
    int noV = 1, noA = 1, noI = engineersCnt, noT = testerCnt;

    //provjera postoji li vec projekt sa zadanim imenom
    std::vector<Project>::iterator si;
    for(si = projects.begin(); si!=projects.end(); si++)
         if((*si).getName() == projectName) { std::cout<<" Project with given name already exists!"<<std::endl; return;}

    //pronadi projekt s danim imenom i nacini tim tako da redom trazis slobodne zaposlenike (koji trenutno nisu u nekom projektu)
        std::vector<ShrEmployee >::iterator it;
        for(it = employees.begin(); it != employees.end(); ++it) {
            if((*it)->getInProject() == false && (noV!=0 || noA!=0 || noI!=0 || noT!=0)) {
                switch((*it)->getCategory()) {
                    case 'V':
                        if(noV == 0) break;
                        newProject.takeEmployee(*it);
                        noV--;  break;
                    case 'A':
                         if(noA == 0) break;
                        newProject.takeEmployee(*it);
                        noA--;  break;
                    case 'I':
                        if(noI == 0) break;
                        newProject.takeEmployee(*it);
                        noI--; break;
                    case 'T':
                        if(noT == 0) break;
                        newProject.takeEmployee(*it);
                        noT--; break;
                }
            }
        }

    //ako nemamo dovoljno zaposlenika za projekt, zaposli nove
        if(noV!=0) {
            std::string code = "";
            char category = 'V';
            double salary = 0, bonus = 0;
            unsigned int Size = employees.size();
            std::cout<<std::endl<<" There are no available team leaders, hire 1 new!"<<std::endl;
            while( employees.size() != Size + 1 ) {
                inputNew(code, category, salary, bonus);
                Hire(code, category , salary, bonus);
                employees.back()->setneedExtra(true);
                }
            newProject.takeEmployee(employees.back());
            }
        if(noA!=0) {
            std::string code = "";
            char category = 'A';
            double salary = 0, bonus = 0;
            unsigned int Size = employees.size();
            std::cout<<std::endl<<" No available architects, hire 1 new!"<<std::endl;
            while( employees.size() != Size + 1 ) {
                inputNew(code, category, salary, bonus);
                Hire(code, category, salary, bonus);
                employees.back()->setneedExtra(true);
             }
            newProject.takeEmployee(employees.back());
            }
        if(noI!=0) {
            int cnt = noI;
            for(int i=0; i<noI; i++) {
                std::cout<<std::endl<<" No available engineers, hire "<<cnt<<" new!"<<std::endl;
                std::string code = "";
                char category = 'I';
                double salary = 0, bonus = 0;
                unsigned int Size = employees.size();
                while( employees.size() != Size + 1 ) {
                    inputNew(code, category, salary, bonus);
                    Hire(code, category, salary, bonus);
                    employees.back()->setneedExtra(true);
                    }
                newProject.takeEmployee(employees.back());
                cnt--;
            }
        }
        if(noT!=0) {
            int cnt = noT;
            for(int i=0; i<noT; i++) {
                std::cout<<std::endl<<" No available testers, hire "<<cnt<<" new!"<<std::endl;
                std::string code = "";
                char category = 'T';
                double salary = 0, bonus = 0;
                unsigned int Size = employees.size();
                while( employees.size() != Size + 1 ) {
                    inputNew(code, category, salary, bonus);
                    Hire(code, category, salary, bonus);
                    employees.back()->setneedExtra(true);
                }
                newProject.takeEmployee(employees.back());
                cnt--;
                }
        }

    projects.push_back(newProject);
    std::cout<<std::endl<<" Project successfully created!"<<std::endl<<std::endl;
}

/**Display team**/
void Company::DisplayTeam(std::string projectName) {

    if(projects.empty()) {
        std::cout<<" There are no active projects!"<<std::endl;
        return;
    }
    unsigned int br = 0;

    //pronadi projekt sa zadanim imenom i prikazi sve zaposlenike u timu
    std::vector<Project>::iterator it;
    for(it = projects.begin(); it != projects.end(); ++it) {
        if((*it).getName() == projectName) {
            std::cout<<std::endl<<" There are "<<(*it).getTeam().size()<<" members in a project "<<(*it).getName()<<":"<<std::endl<<std::endl;
            (*it).displayTeam();
            break;
        }
        br++;
    }
    if(br == projects.size()) {
        std::cout<<" Project with a given name doesn't exists!"<<std::endl;
    }

}

/**Get project cost**/
 double Company::GetProjectCost(std::string projectName, int duration) {

        double costV = 0, costA = 0, costI = 0, costT = 0, Cost = 0, R;
        int T;
        unsigned int br = 0;

        std::vector<Project>::iterator it;

        if(projects.empty()) {
            return -1;
        }

        //pronadi projekt s danim imenom
        for(it = projects.begin(); it!=projects.end(); it++)  {
            if((*it).getName() == projectName) {

                if((*it).getFinished() == true ) {
                    std::cout<<std::endl<<"Project is already finished with duration of "<<(*it).getDuration()<<" h!"<<std::endl;
                    T = (*it).getDuration();

                    }
                else T = duration;

                //iteriraj po svim zaposlenicima u timu i racunaj trosak za svaku kategoriju zaposlenika
                for(unsigned int i=0; i<(*it).getTeam().size(); i++ ) {

                    //Voditelj
                    if((*it).getTeam()[i]->getCategory() == 'V') {
                        //ako smo voditelja morali dodatno zasposliti, u trosak uracunaj i trosak zaposljavanja
                        if((*it).getTeam()[i]->getneedExtra() == true ) R = hCost;
                        else R = 0;
                        ShrLeader L = std::dynamic_pointer_cast<TeamLeader> ((*it).getTeam()[i]);
                        if(L!=nullptr)
                        costV = T * ((L->getSalary())/180) + L->getBonus() + R;
                    }
                    //Arhitekt
                    if((*it).getTeam()[i]->getCategory() == 'A') {
                        if((*it).getTeam()[i]->getneedExtra() == true ) R = hCost;
                        else R = 0;
                        costA = 0.5 * T * (((*it).getTeam()[i]->getSalary())/180) + R;
                    }
                    //Inženjer
                    if((*it).getTeam()[i]->getCategory() == 'I') {
                        if((*it).getTeam()[i]->getneedExtra() == true ) R = hCost;
                        else R = 0;
                        std::random_device rd; // obtain a random number from hardware
                        std::mt19937 eng(rd()); // seed the generator
                        std::uniform_int_distribution<> distr(T/2, T);
                        costI += distr(eng) * (((*it).getTeam()[i]->getSalary())/180) + R;
                    }
                    //Tester
                    if((*it).getTeam()[i]->getCategory() == 'T') {
                        if((*it).getTeam()[i]->getneedExtra() == true ) R = hCost;
                        else R = 0;

                        if(T <= 240 )
                            costT += (T/24)*(((*it).getTeam()[i]->getSalary())/180) + R;
                        else if(T>240 && T <=720)
                            costT += (4*T/72)*(((*it).getTeam()[i]->getSalary())/180) + R;
                        else if(T > 720)
                            costT += 50*(((*it).getTeam()[i]->getSalary())/180) + R;
                        }

                    }
                     break;
                }
                br++;
            }
        if(br == projects.size()+1) {
            return -1;
            }

        Cost = costV + costA + costI + costT;

        return Cost;

 }


/**Finish project**/
void Company::FinishProject(std::string projectName, int duration) {

     std::vector<Project>::iterator it;
    for(it = projects.begin(); it!=projects.end(); it++)
        if((*it).getName() == projectName && (*it).getFinished()==false) {
            (*it).releaseTeam();
            (*it).setDuration(duration);
            (*it).setFinished();
            std::cout<<"Project "<<(*it).getName()<<" is finished with duration of "<<duration<<" h!"<<std::endl;
        }
        else if((*it).getName() == projectName && (*it).getFinished()==true) {
            std::cout<<" Project is already finished with duration of "<<(*it).getDuration()<<" h!"<<std::endl;
            return;
        }

}















