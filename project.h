#ifndef PROJECT_H_INCLUDED
#define PROJECT_H_INCLUDED

using ShrEmployee = std::shared_ptr<Employee>;
using ShrLeader = std::shared_ptr<TeamLeader>;

class Project {

     public:
        Project(std::string nm) : name(nm), duration(0), finished(false) {}
        std::string getName() { return name; }
        int getDuration() { return duration; }
        void setDuration(int d) { duration = d; }
        bool getFinished() { return finished;}
        void setFinished() { finished = true; }
        std::vector<ShrEmployee>& getTeam() { return team; }
        void displayTeam();
        void takeEmployee(ShrEmployee E) { E->setInProject(true); team.push_back(E);}
        void releaseTeam();
    private:
        std::string name;
        int duration;
        bool finished;
        std::vector<ShrEmployee> team;

};
#endif
