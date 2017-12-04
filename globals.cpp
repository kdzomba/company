#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <memory>
#include "employee.h"
#include "company.h"
#include "project.h"

class Employee;
/**Helper function for user input**/
void inputNew(std::string &c, char &z, double &s, double &b) {

        if(z != 'V' && z != 'A' && z != 'I' && z != 'T')  {

            std::cout<<std::endl;
            std::cout<<"  -----------------------------------------------------------"<<std::endl;
            std::cout<<"  |                          HIRE                           |"<<std::endl;
            std::cout<<"  -----------------------------------------------------------"<<std::endl;
            std::cout<<"  | 'V' - Leader of a project                               |" <<std::endl;
            std::cout<<"  | 'A' - Architect                                         |"  <<std::endl;
            std::cout<<"  | 'I' - Engeineer                                         |" <<std::endl;
            std::cout<<"  | 'T' - Tester                                            |" <<std::endl;
            std::cout<<"-----------------------------------------------------------"<<std::endl;
            std::cout<<"-> Please enter employees category or 'R' to return to previous menu:  ";
            std::cin>>z;
             if(z == 'R') return;
             while(z!='V' && z!='A' && z!='I' && z!='T') {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Incorrect employee category, only 'V', 'A', 'I' and 'T' allowed! Try again!"<<std::endl<<std::endl;
                std::cout<<"Please select employee category or 'R' to return to previous menu: ";
                std::cin>>z;
                }
        }
        std::cout<<"-> Please enter employees unique code:  ";
        std::cin>>c;
        std::cout<<"-> Please enter salary: ";
        std::cin>>s;
        while(!std::cin){
                std::cout << "Bad value!"<<std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout<<"-> Please enter salary: ";
                std::cin>>s;
            }
        if(z=='V') {
            std::cout<<"-> Please enter bonus:  ";
            std::cin>>b;
             while(!std::cin){
                    std::cout << "Bad value!"<<std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout<<"-> Please enter bonus: ";
                    std::cin>>b;
                }
             }
        std::cout<<std::endl;
}

/**MENU**/
void menu() {

    double hCost;
    int option;

    std::cout<<"  -----------------------------------------------------------"<<std::endl;
    std::cout<<"  |                         WELCOME!                        |"<<std::endl;
    std::cout<<"  -----------------------------------------------------------"<<std::endl;
    std::cout<<"-> Enter company hiring cost to proceed: ";
    std::cin>>hCost;
    while(!std::cin){
        std::cout << "Bad value!"<<std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout<<"-> Enter company hiring cost to proceed: ";
        std::cin>>hCost;
        }
    Company C(hCost);

    do {
    std::cout<<"  -----------------------------------------------------------"<<std::endl;
    std::cout<<"  |                          MENU                           |"<<std::endl;
    std::cout<<"  -----------------------------------------------------------"<<std::endl;
    std::cout<<"  | 1. Hire employee                                        |"<<std::endl;
    std::cout<<"  | 2. Save employees to a text file                        |"<<std::endl;
    std::cout<<"  | 3. Load employees from a text file                      |"<<std::endl;
    std::cout<<"  | 4. Create new project                                   |"<<std::endl;
    std::cout<<"  | 5. Display team                                         |"<<std::endl;
    std::cout<<"  | 6. Get project cost                                     |"<<std::endl;
    std::cout<<"  | 7. Finish project                                       |"<<std::endl;
    std::cout<<"  | 8. Exit                                                 |"<<std::endl;
    std::cout<<"  -----------------------------------------------------------"<<std::endl;
    std::cout<<"-> Please select an option: ";
    std::cin>>option;
    while(option!=1 &&  option!=2  && option!=3  && option!=4  && option!=5  && option!=6  && option!=7  && option!=8){
            std::cout << "Bad value!"<<std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout<<"-> Please select an option: ";
            std::cin>>option;
            }

    if(option == 1) {
        char cat = ' ';
        double salary=0, bonus=0;
        std::string code = "";

       do {
            inputNew(code, cat, salary, bonus);
            if(cat == 'R') break;
            C.Hire(code, cat, salary, bonus);
            cat = ' ';
        }
        while(cat!='R');
    }
    else if(option == 2) {
        std::string txtname;
        char n;
        std::cout<<"-> Please enter textfile name to save employees: ";
        std::cin>>txtname;
        C.SaveEmployees(txtname);
        std::cout<<" Enter any key to return to menu or 'Q' to close program:  ";
        std::cin>>n;
        if(n == 'Q') break;
        else continue;
    }
    else if(option == 3) {
        std::string txtname;
        char n;
        std::cout<<"-> Please enter textfile name to load employees: ";
        std::cin>>txtname;
        C.LoadEmployees(txtname);
        std::cout<<" Enter any key to return to menu or 'Q' to close program:  ";
        std::cin>>n;
        if(n == 'Q') break;
        else continue;
    }
    else if(option == 4) {
        std::string name;
        int noI, noT;
        char n;
        std::cout<<"-> Please enter project name: ";
        std::cin>>name;
        std::cout<<"-> Please enter number of engineers for a project: ";
        std::cin>>noI;
        while(!std::cin){
            std::cout << "Bad value!"<<std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout<<"-> Please enter number of engineers for a project: ";
            std::cin>>noI;
            }

        std::cout<<"-> Please enter number of testers for a project: ";
        std::cin>>noT;
        while(!std::cin){
            std::cout << "Bad value!"<<std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout<<"-> Please enter number of testers for a project: ";
            std::cin>>noT;
            }
        C.CreateProject(name, noI, noT);
        std::cout<<" Enter any key to return to menu or 'Q' to close program:  ";
        std::cin>>n;
        if(n == 'Q') break;
        else continue;

    }
    else if(option == 5) {
        std::string name;
        char n;
        std::cout<<"-> Enter project name to display team:  ";
        std::cin>>name;
        C.DisplayTeam(name);
        std::cout<<std::endl<<" Enter any key to return to menu or 'Q' to close program: ";
        std::cin>>n;
        if(n == 'Q') break;
        else continue;
    }
    else if(option == 6) {
        std::string name;
        int duration;
        char n;
        std::cout<<"-> Enter project name: ";
        std::cin>>name;
        std::cout<<"-> Enter project duration: ";
        std::cin>>duration;
        while(!std::cin){
            std::cout << "Bad value!"<<std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout<<"-> Enter project duration: ";
            std::cin>>duration;
            }
        double cost = C.GetProjectCost(name, duration);
        if(cost !=-1)
            std::cout<<"Cost for project "<<name<<" is: "<<cost<<std::endl;
        else
            std::cout<<"Project with a given name doesn't exist!"<<std::endl;
        std::cout<<std::endl<<" Enter any key to return to menu or 'Q' to close program: ";
        std::cin>>n;
        if(n == 'Q') break;
        else continue;
    }

    else if(option == 7) {
        char n;
        int duration;
        std::string name;
        std::cout<<"-> Please enter project name You want to finish:  ";
        std::cin>>name;
        std::cout<<"-> Enter duration:  ";
        std::cin>>duration;

        C.FinishProject(name,duration );
        std::cout<<std::endl<<" Enter any key to return to menu or 'Q' to close program: ";
        std::cin>>n;
        if(n == 'Q') break;
        else continue;
    }
    else if(option == 8) { break;}

    }

    while(option!=8);
    std::cout<<std::endl;

}

