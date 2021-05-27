//
// Created by User on 21/05/2021.
//

#include "System.h"


void System::addPortToDictionary(const shared_ptr<Port> &p) {
    ports_dictionary.insert(pair<int, shared_ptr<Port>>(p->getID(), p));
}


int System::portExist(string &other_port_name) const {
    //return port ID if port exist. else: -1;
    for (auto p :ports_dictionary) {
        if (p.second->getPortName() == other_port_name) { return p.first; }
    }
    return -1;
}

//Global func
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

void System::addPortToGraph(Graph &g, int src_portID, int dst_portID, int dis_cap) {
    //update distance graph
    bool done = false;
    //search if edge already exist
    for (auto e: distanceGraph.graph) {
        if (e.first == src_portID) {
            //src exist
            if (e.second.isEmpty()) {
                weak_ptr<Port> w(ports_dictionary.find(dst_portID)->second);
                vector<int> dis;
                dis.push_back(dis_cap);
                Dst dst{w, dis};
                e.second.add(dst);
                done = true;
                break;
            }
            e.second.setToHead();
            while (!e.second.endOfLinkedList()) {
                if (e.second.getCursor().lock()->data.port.lock()->getID() == dst_portID) {
                    //src equal&dst equal
                    e.second.getCursor().lock()->data.addTimeOrCapacity(dis_cap);
                    done = true;
                    break;
                }
                ++e.second;
            }
            if (!done) {
                //only src exist
                weak_ptr<Port> w(ports_dictionary.find(dst_portID)->second);
                vector<int> dis;
                dis.push_back(dis_cap);
                Dst dst{w, dis};
                e.second.add(dst);
                done = true;
                break;
            }

            ++e.second;
        }
    }
    if (!done) {
        distanceGraph.addVertex(src_portID);
        weak_ptr<Port> w(ports_dictionary.find(dst_portID)->second);
        vector<int> dis;
        dis.push_back(dis_cap);
        Dst dst{w, dis};
        Edge edge{src_portID, dst};
        distanceGraph.addEdge(edge);
    }
}

//void System::load(const char *file_name) {
//    string line, src_port_name, time;
//    int src_transporting = 0;
//    ifstream in_file(file_name);
//    //TODO: exceptions
//    if (!in_file) { cerr << "file cannot be open"; }
//
////first getting the source port details
//    getline(in_file, line);
//    src_port_name = line.substr(0, line.find(','));
//    int src_ID;
//    if ((src_ID = portExist(src_port_name)) == -1) {
//        src_ID = ports_counter++;
//        addPortToDictionary(shared_ptr<Port>(new Port(src_ID, src_port_name)));
//        containersGraph.addVertex(src_ID);
//    }
//
//
//    time = line.substr(line.find(',') + 1);
//    int d, m, h, min, curr_ID, prev_id;
//    string_to_time(time, d, m, h, min);
//    Time src_leaving_time = Time(d, m, h, min);
//    Time prev_leaving = src_leaving_time;
//    prev_id = src_ID;
//
//    string arrive_time, leave_time, capacity, current_port_name;
//    while (getline(in_file, line)) {
//        int first_psik = line.find(',');
//        int second_psik = line.find(',', first_psik + 1);
//        int third_psik = line.find(',', second_psik + 1);
//
//        current_port_name = line.substr(0, first_psik);
//        if ((curr_ID = portExist(current_port_name)) == -1) {
//            curr_ID = ports_counter++;
//            addPortToDictionary(shared_ptr<Port>(new Port(curr_ID, current_port_name)));
//        }
//
//        arrive_time = line.substr(first_psik + 1, second_psik - first_psik - 1);
//        leave_time = line.substr(third_psik + 1);
//        capacity = line.substr(second_psik + 1, third_psik - second_psik - 1);
//        int cap = stoi(capacity);
//
//        int d, m, h, min;
//        string_to_time(arrive_time, d, m, h, min);
//        Time arrive_to_port_time = Time(d, m, h, min);
//        string_to_time(leave_time, d, m, h, min);
//        Time leave_port_time = Time(d, m, h, min);
//
//        ports_dictionary.find(curr_ID)->second->setBalance(cap, arrive_to_port_time);
//
//        int time_from_prev_to_curr = arrive_to_port_time.minutesSinceTime(prev_leaving);
////***
//        //update distance graph
//        bool dis_done = false;
//        //search if edge already exist
//        for (auto e: distanceGraph.graph) {
//            if (e.first == prev_id) {
//                //src exist
//                if (e.second.isEmpty()) {
//                    weak_ptr<Port> w(ports_dictionary.find(curr_ID)->second);
//                    vector<int> dis;
//                    dis.push_back(time_from_prev_to_curr);
//                    Dst dst{w, dis};
//                    e.second.add(dst);
//                    dis_done = true;
//                    break;
//                }
//                e.second.setToHead();
//                while (!e.second.endOfLinkedList()) {
//                    if (e.second.getCursor().lock()->data.port.lock()->getID() == curr_ID) {
//                        //src equal&dst equal
//                        e.second.getCursor().lock()->data.addTimeOrCapacity(time_from_prev_to_curr);
//                        dis_done = true;
//                        break;
//                    }
//                }
//                if (!dis_done) {
//                    //only src exist
//                    weak_ptr<Port> w(ports_dictionary.find(curr_ID)->second);
//                    vector<int> dis;
//                    dis.push_back(time_from_prev_to_curr);
//                    Dst dst{w, dis};
//                    e.second.add(dst);
//                    dis_done = true;
//                    break;
//                }
//
//                ++e.second;
//            }
//        }
//        if (!dis_done) {
//            distanceGraph.addVertex(prev_id);
//            weak_ptr<Port> w(ports_dictionary.find(curr_ID)->second);
//            vector<int> dis;
//            dis.push_back(time_from_prev_to_curr);
//            Dst dst{w, dis};
//            Edge edge{prev_id, dst};
//            distanceGraph.addEdge(edge);
//        }
//////*********
//        //update containers graph
//        bool contain_done = false;
//        //search if edge already exist
//        for (auto e: containersGraph.graph) {
//            if (e.first == src_ID) {
//                //src exist
//                if (e.second.isEmpty()) {
//                    weak_ptr<Port> w(ports_dictionary.find(curr_ID)->second);
//                    vector<int> capy;
//                    capy.push_back(cap);
//                    Dst dst{w, capy};
//                    e.second.add(dst);
//                    contain_done = true;
//                    break;
//                }
//                e.second.setToHead();
//                while (!e.second.endOfLinkedList()) {
//                    if (e.second.getCursor().lock()->data.port.lock()->getID() == curr_ID) {
//                        //src equal&dst equal
//                        e.second.getCursor().lock()->data.addTimeOrCapacity(cap);
//                        contain_done = true;
//                        break;
//                    }
//                }
//                if (!contain_done) {
//                    //only src exist
//                    weak_ptr<Port> w(ports_dictionary.find(curr_ID)->second);
//                    vector<int> capy;
//                    capy.push_back(cap);
//                    Dst dst{w, capy};
//                    e.second.add(dst);
//                    contain_done = true;
//                    break;
//                }
//
//                ++e.second;
//            }
//        }
//        if (!contain_done) {
//            containersGraph.addVertex(prev_id);
//            weak_ptr<Port> w(ports_dictionary.find(curr_ID)->second);
//            vector<int> capy;
//            capy.push_back(cap);
//            Dst dst{w, capy};
//            Edge edge{prev_id, dst};
//            containersGraph.addEdge(edge);
//        }
//////*****
//
//
////        else {  TODO: if edge exist: add capacity to vector of capacities
////            cout <<"inside"<<endl;
////            for (auto e: containersGraph.graph) {
////                if (e.first == src_ID) {
////                    if(e.second.isEmpty()){continue;}
////                    e.second.setToHead();
////                    while (!e.second.endOfLinkedList()) {
////                        if (e.second.getCursor().lock()->data.port.lock()->getID() == curr_ID) {
////                            e.second.getCursor().lock()->data.addTimeOrCapacity(cap);
////                            break;
////                        }
////                        ++e.second;
////                    }
////                }
////            }
////        }
//
//        prev_leaving = leave_port_time;
//        prev_id = curr_ID;
//        src_transporting += cap;
//
//    }
//
//    ports_dictionary.
//                    find(src_ID)
//            ->second->setBalance((-1 * src_transporting), src_leaving_time);
//
//}
void System::load(const char *file_name) {
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
        src_ID = ports_counter++;
        addPortToDictionary(shared_ptr<Port>(new Port(src_ID, src_port_name)));
        containersGraph.addVertex(src_ID);
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
            curr_ID = ports_counter++;
            addPortToDictionary(shared_ptr<Port>(new Port(curr_ID, current_port_name)));
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

        ports_dictionary.find(curr_ID)->second->setBalance(cap, arrive_to_port_time);

        int time_from_prev_to_curr = arrive_to_port_time.minutesSinceTime(prev_leaving);
        addPortToGraph(distanceGraph, prev_id, curr_ID, time_from_prev_to_curr);

        vector<int> v2;
        v2.push_back(cap);
        weak_ptr<Port> w(ports_dictionary.find(curr_ID)->second);
        Dst dst{w, v2};

        containersGraph.graph.find(src_ID)->second.add(dst);

        prev_leaving = leave_port_time;
        prev_id = curr_ID;
        src_transporting += cap;

    }

    ports_dictionary.find(src_ID)->second->setBalance((-1 * src_transporting), src_leaving_time);

}

void System::printTimesGraph() {
    for (int i = 0; i < distanceGraph.getSize(); i++) {
        // print the current vertex number
        string curr_prt = "<" + ports_dictionary.find(i)->second->getPortName() + ">";

        // print all neighboring vertices of a vertex `i`
        distanceGraph.graph.find(i)->second.setToHead();
        while (!distanceGraph.graph[i].endOfLinkedList()) {
            cout << curr_prt << " ---"
                 << distanceGraph.graph.find(i)->second.getCursor().lock().get()->data.getAverageDistance()
                 << "---> ";
            cout << ports_dictionary.find(
                    distanceGraph.graph.find(
                            i)->second.getCursor().lock().get()->data.port.lock()->getID())->second->getPortName()
                 << " " << endl;
            ++distanceGraph.graph.find(i)->second;
        }

    }
}

void System::printContainersGraph() {
    for (int i = 0; i < containersGraph.getSize(); i++) {
        // print the current vertex number
        cout << "<" << ports_dictionary.find(i)->second->getPortName() << ">";

        // print all neighboring vertices of a vertex `i`
        containersGraph.graph[i].setToHead();
        while (!containersGraph.graph[i].endOfLinkedList()) {
            cout << " ---" << containersGraph.graph[i].getCursor().lock().get()->data.getToatalCapacity()
                 << "---> ";
            cout << ports_dictionary.find(
                    containersGraph.graph[i].getCursor().lock().get()->data.port.lock()->getID())->second->getPortName()
                 << " ";
            ++containersGraph.graph[i];
        }
        cout << endl;
    }
}

void System::outbound(int port_id) const {
    for (auto e: distanceGraph.graph) {
        if (e.first == port_id) {
            e.second.setToHead();
            while (!e.second.endOfLinkedList()) {
                cout << e.second.getCursor().lock()->data.port.lock()->getPortName() << ","
                     << e.second.getCursor().lock()->data.getAverageDistance() << endl;
                ++e.second;
            }
            return;
        }
    }
    cout << ports_dictionary.find(port_id)->second->getPortName() << ": no outbound ports" << endl;
}

void System::inbound(int port_id) const {
    bool not_found = true;
    for (auto e: distanceGraph.graph) {
        string curr_src = ports_dictionary.find(e.first)->second->getPortName();
        e.second.setToHead();
        while (!e.second.endOfLinkedList()) {
            if (e.second.getCursor().lock()->data.port.lock()->getID() == port_id) {
                cout << curr_src << "," << e.second.getCursor().lock()->data.getAverageDistance() << endl;
                not_found = false;
                break;
            }
            ++e.second;
        }
    }
    if (not_found) {
        cout << ports_dictionary.find(port_id)->second->getPortName() << ": no inbound ports" << endl;
    }


}

