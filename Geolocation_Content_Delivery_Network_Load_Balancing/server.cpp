#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <unordered_map>
#include <limits>
using namespace std;

unordered_map<int,int>origin_server{
    {1,100},
    {2,200},
    {3,300},
    {4,400},
    {5,500},
    {6,600}
};

struct Node{
    int key;
    int value;
    int cnt;
    Node* prev;
    Node* next;
    Node(int k,int v)
    {
        key=k;
        value=v;
        cnt=1;
        prev=NULL;
        next=NULL;
    }
};
struct List{
    int size;
    Node* head;
    Node* tail;
    List()
    {
        head=new Node(0,0);
        tail=new Node(0,0);
        head->next=tail;
        tail->prev=head;
        size=0;
    }
    void addNode(Node* node)
    {
        node->next=head->next;
        node->prev=head;
        head->next->prev=node;
        head->next=node;
        size++;
    }
    void deleteNode(Node* node)
    {
        node->next->prev=node->prev;
        node->prev->next=node->next;
        size--;
    }
};
class LFUCache{
    map<int,Node*>keyNode;
    map<int,List*>freqListMap;
    int maxSizeCache;
    int minFreq;
    int curSize;
public:
    LFUCache(int capacity) {
        maxSizeCache=capacity;
        minFreq=0;
        curSize=0;
    }
    void UpdateFreqListMap(Node* node)
    {
        keyNode.erase(node->key);
        freqListMap[node->cnt]->deleteNode(node);
        if(node->cnt==minFreq && freqListMap[node->cnt]->size==0)
        {
            minFreq++;
        }
        List* nextfreq=new List();
        if(freqListMap.find(node->cnt + 1)!=freqListMap.end())
        {
            nextfreq=freqListMap[node->cnt + 1];
        }
        node->cnt=node->cnt + 1;
        nextfreq->addNode(node);
        freqListMap[node->cnt]=nextfreq;
        keyNode[node->key]=node;
    }
    int get(int key) {
        int ans=-1;
        if(keyNode.find(key)!=keyNode.end())
        {
            Node* temp=keyNode[key];
            ans=temp->value;
            UpdateFreqListMap(temp);
        }
        if(ans==-1)
        {
            if(origin_server.find(key)!=origin_server.end())
            {
                put(key,origin_server[key]);
                ans=origin_server[key];
            }
        }
        return ans;
    }

    void put(int key, int value) {
        if(maxSizeCache==0)
        {
            return;
        }
        if(keyNode.find(key)!=keyNode.end())
        {
            Node* temp=keyNode[key];
            temp->value=value;
            UpdateFreqListMap(temp);
        }
        else
        {
            if(curSize==maxSizeCache)
            {
                List* list=freqListMap[minFreq];
                keyNode.erase(list->tail->prev->key);
                freqListMap[minFreq]->deleteNode(list->tail->prev);
                curSize--;
            }
            curSize++;
            minFreq=1;
            List* listFreq=new List();
            if(freqListMap.find(minFreq)!=freqListMap.end())
            {
                listFreq=freqListMap[minFreq];
            }
            Node* node=new Node(key,value);
            listFreq->addNode(node);
            keyNode[key]=node;
            freqListMap[minFreq]=listFreq;
        }
    }
};
class Server {
public:
    std::string ipAddress;
    double latitude;
    double longitude;
    int numRequests;
    LFUCache* lfuCache;
public:
    // Constructor
    Server()
    {
        numRequests=0;
        lfuCache=new LFUCache(5);
    }
    int get(int key)
    {
        numRequests++;
        return lfuCache->get(key);
    }
    void printDetails(){
    std::cout << "Server IP: " << ipAddress << "\n"
                  << "Latitude: " << latitude << "\n"
                  << "Longitude: " << longitude << "\n"
                  << "Number of Requests: " << numRequests << "\n";
    }

};
