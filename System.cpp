//
// Created by User on 21/05/2021.
//

#include "System.h"


void System::addPort(Port &p) {
    ports_dictionary.insert(pair<int, Port>(p.getID(), p));
}


int System::portExist(string &other_port_name) const {
    //return port ID if port exist. else: -1;
    for (auto p :ports_dictionary) {
        if (p.second.getPortName() == other_port_name) { return p.first; }
    }
    return -1;
}

bool System::edgeExist(int srcID, Port dst) {
    for (auto e: distanceGraph.graph) {
        if(e.second.getHead().get() == NULL){continue;}
        int curr_dstID = e.second.getHead().get()->data.port.getID();
        if (e.first == srcID && curr_dstID == dst.getID()) { return true; }
        if (e.first == dst.getID() && curr_dstID == srcID) { return true; }
        return false;
    }
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
    string line, src_port_name, time;
    int src_transporting = 0;
    ifstream in_file(file_name);
    //TODO: exceptions
    if (!in_file) { cerr << "file cannot be open"; }

//first getting the source port details
    getline(in_file, line);
    src_port_name = line.substr(0, line.find(','));
    int src_ID;
    if ((src_ID = portExist(src_port_name)) == -1) {
        Port srcPort = Port(ports_counter++, src_port_name);
        addPort(srcPort);
        containersGraph.addVertex(srcPort.getID());
        src_ID = srcPort.getID();
    }


    time = line.substr(line.find(',') + 1);
    int d, m, h, min, curr_ID, prev_id;
    string_to_time(time, d, m, h, min);
    Time src_leaving_time = Time(d, m, h, min);
    Time prev_leaving = src_leaving_time;
    prev_id = src_ID;

    string arrive_time, leave_time, capacity, current_port_name;
    while (getline(in_file, line)) {
        int first_psik = line.find(',');
        int second_psik = line.find(',', first_psik + 1);
        int third_psik = line.find(',', second_psik + 1);

        current_port_name = line.substr(0, first_psik);
        if ((curr_ID = portExist(current_port_name)) == -1) {
            Port p = Port(ports_counter++, current_port_name);
            addPort(p);
            curr_ID = p.getID();
        }

        arrive_time = line.substr(first_psik + 1, second_psik - first_psik - 1);
        leave_time = line.substr(third_psik + 1);
        capacity = line.substr(second_psik + 1, third_psik - second_psik - 1);
        int cap = stoi(capacity);

        int d, m, h, min;
        string_to_time(arrive_time, d, m, h, min);
        Time arrive_to_port_time = Time(d, m, h, min);
        string_to_time(leave_time, d, m, h, min);
        Time leave_port_time = Time(d, m, h, min);

        ports_dictionary.find(curr_ID)->second.setBalance(cap, arrive_to_port_time);

        int time_from_prev_to_curr = arrive_to_port_time.minutesSinceTime(prev_leaving);
        //update distance graph
        distanceGraph.addVertex(prev_id);
        if (!edgeExist(prev_id, ports_dictionary.find(curr_ID)->second)) {
            //edge from src to dst doesnt exist
            vector<int> v1;
            v1.push_back(time_from_prev_to_curr);
            Dst curr{ports_dictionary.find(curr_ID)->second, v1};
            Edge edge{prev_id, curr};
            distanceGraph.addEdge(edge);
        } else {
            //edge from src to dst exist
            for (auto e: distanceGraph.graph) {
                int curr_dstID = e.second.getHead().get()->data.port.getID();
                if ((e.first == prev_id && curr_dstID == curr_ID) || (e.first == curr_ID && curr_dstID == prev_id)) {
                    e.second.getHead()->data.addTime(time_from_prev_to_curr);
                }
            }
        }

        //update containers graph

        vector<int> v2;
        v2.push_back(cap);
        Dst dst{ports_dictionary.find(curr_ID)->second, v2};
        containersGraph.graph.find(src_ID)->second.add(dst);

        prev_leaving = leave_port_time;
        prev_id = curr_ID;
        src_transporting += cap;

    }

    ports_dictionary.find(src_ID)->second.setBalance((-1 * src_transporting), src_leaving_time);

}

void System::printTimesGraph() {
    for (int i = 0; i < distanceGraph.getSize(); i++) {
        // print the current vertex number
        cout << ports_dictionary.find(i)->second.getPortName();

        // print all neighboring vertices of a vertex `i`
        distanceGraph.graph[i].setToHead();
        while (!distanceGraph.graph[i].endOfLinkedList()) {
            cout << " ---" << distanceGraph.graph[i].getCursor().lock().get()->data.getAverageDistance() << "---> ";
            cout << ports_dictionary.find(
                    distanceGraph.graph[i].getCursor().lock().get()->data.port.getID())->second.getPortName()
                 << " ";
            ++distanceGraph.graph[i];
        }
        cout << endl;
    }
}

void System::printContainersGraph() {
    for (int i = 0; i < containersGraph.getSize(); i++) {
        // print the current vertex number
        cout << ports_dictionary.find(i)->second.getPortName();

        // print all neighboring vertices of a vertex `i`
        containersGraph.graph[i].setToHead();
        while (!containersGraph.graph[i].endOfLinkedList()) {
            cout << " ---" << containersGraph.graph[i].getCursor().lock().get()->data.getToatalCapacity() << "---> ";
            cout << ports_dictionary.find(
                    containersGraph.graph[i].getCursor().lock().get()->data.port.getID())->second.getPortName()
                 << " ";
            ++containersGraph.graph[i];
        }
        cout << endl;
    }
}

