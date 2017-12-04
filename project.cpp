#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "employee.h"
#include "project.h"

void Project::displayTeam() {

    std::vector<ShrEmployee>::iterator it;
    for(it = team.begin(); it != team.end(); it++) {
        std::cout<<"Code: "<<(*it)->getCode()<<"  Category: "<<(*it)->getCategory()<<"  Salary: "<<(*it)->getSalary();
        if((*it)->getCategory() == 'V') {
            ShrLeader L = std::dynamic_pointer_cast<TeamLeader> (*it);
            if(L!=nullptr)
                std::cout<<"  Bonus: "<<L->getBonus()<<std::endl;
            }
        else std::cout<<std::endl;
        }
}

void Project::releaseTeam() {

        std::vector<ShrEmployee>::iterator it;
        for(it = team.begin(); it!=team.end(); it++) {
            if((*it)->getneedExtra() == true )
                (*it)->setneedExtra(false);
            (*it)->setInProject(false);
        }
}
