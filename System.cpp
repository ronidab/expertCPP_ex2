//
// Created by User on 21/05/2021.
//

#include "System.h"


void System::addPort(Port &p) {
    ports_dictionary.insert(pair<int, Port>(p.getID(), p));
}

void string_to_time(string time, int &day, int &month, int &hour, int &minutes) {
    string d = time.substr(0, 2);
    day = stoi(d);
    string m = time.substr(time.find('/') + 1, 2);
    month = stoi(m);
    string h = time.substr(time.find(' ') + 1, 2);
    hour = stoi(h);
    string min = time.substr(time.find(':') + 1, 2);
    minutes = stoi(min);
}

void System::init(const char *file_name) {
    string line, src_port_name, current_port, time;
    int src_transporting = 0;
    ifstream in_file(file_name);
    //TODO: exceptions
    if (!in_file) { cerr << "file cannot be open"; }

//first getting the source port details
    getline(in_file, line);
    src_port_name = line.substr(0, line.find(','));
    Port srcPort = Port(ports_counter++, src_port_name);
    addPort(srcPort);

    containersGraph.addVertex(srcPort.getID());

    time = line.substr(line.find(',') + 1);
    int d, m, h, min;
    string_to_time(time, d, m, h, min);
    Time src_leaving_time = Time(d, m, h, min);
    Time prev_leaving = src_leaving_time;
    int prev_id = srcPort.getID();

    string arrive_time, leave_time, capacity;
    while (getline(in_file, line)) {
        int first_psik = line.find(',');
        int second_psik = line.find(',',first_psik+1);
        int third_psik = line.find(',',second_psik+1);

        current_port = line.substr(0, first_psik);
        Port p = Port(ports_counter++, current_port);
        addPort(p);

        arrive_time = line.substr(first_psik + 1,second_psik-first_psik-1);
        leave_time = line.substr(third_psik+1);
        capacity = line.substr(second_psik+1,third_psik-second_psik-1);
        int cap = stoi(capacity);

        int d, m, h, min;
        string_to_time(arrive_time, d, m, h, min);
        Time arrive_to_port_time = Time(d, m, h, min);
        string_to_time(leave_time, d,m,h,min);
        Time leave_port_time = Time(d,m,h,min);

        p.setBalance(cap, arrive_to_port_time);

        int time_from_prev_to_curr = arrive_to_port_time.minutesSinceTime(prev_leaving);
        distanceGraph.addVertex(p.getID()-1);
        Dst curr {p,time_from_prev_to_curr};
        Edge edge {prev_id, curr};
        distanceGraph.addEdge(edge);
        //update containers graph
        Dst dst{ p, cap};
        containersGraph.graph.find(srcPort.getID())->second.add(dst);

        prev_leaving = leave_port_time;
        prev_id = p.getID();
        src_transporting += cap;

    }

    srcPort.setBalance((-1*src_transporting), src_leaving_time);

}


void System::printTimesGraph() {
    for (int i = 0; i < distanceGraph.getSize() ; i++) {
        // print the current vertex number
        cout << ports_dictionary.find(i)->second.getPortName() << " ---";

        // print all neighboring vertices of a vertex `i`
        distanceGraph.graph[i].setToHead();
        while(!distanceGraph.graph[i].endOfLinkedList()){
            cout << distanceGraph.graph[i].getCursor().lock().get()->data.distance_or_capacity << "---> ";
            cout << ports_dictionary.find(distanceGraph.graph[i].getCursor().lock().get()->data.port.getID())->second.getPortName() << " ";
            ++distanceGraph.graph[i];
        }
        cout << endl;
    }
}


void System::printContainersGraph() {
    for (int i = 0; i < containersGraph.getSize() ; i++) {
        // print the current vertex number
        cout << ports_dictionary.find(i)->second.getPortName();

        // print all neighboring vertices of a vertex `i`
        containersGraph.graph[i].setToHead();
        while(!containersGraph.graph[i].endOfLinkedList()){
            cout  << " ---"<< containersGraph.graph[i].getCursor().lock().get()->data.distance_or_capacity << "---> ";
            cout << ports_dictionary.find(containersGraph.graph[i].getCursor().lock().get()->data.port.getID())->second.getPortName() << " ";
            ++containersGraph.graph[i];
        }
        cout << endl;
    }
}

//void System::printContainersGraph(){
//    for(int i=0; i<containersGraph.getSize(); i++){
//        cout << ports_dictionary.find(i)->second.getPortName();
//
////        for(Dst d: containersGraph.find(i)->second){
////            cout <<" --"<<d.distance_or_capacity<<"--> "<<ports_dictionary.find(d.id)->second.getPortName();
////        }
//        cout <<endl;
//    }
//}