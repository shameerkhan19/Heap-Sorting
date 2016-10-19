#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <stdexcept>

using namespace std;

class PQSort{
private:
    int *PQAry;
    int size;//just so i don't have to type PQAry[0] every time.
    int capacity;
    char* args1;
    char* args2;
    char* args3;

public:
    PQSort(){};
    PQSort(int x){
        capacity=x+1;
        PQAry=new int[capacity];
        for(int i=1;i<capacity;i++)//doing this to keep the print look nice. Otherwise for the index's which are unassigned i get some weried large numbers until assigned.
            PQAry[i]=0;
        PQAry[0]=0;
        size=PQAry[0];
    }
    void setArgs1(char* arg){
        args1=arg;
    }

    void setArgs2(char* arg){
        args2=arg;
    }

    void setArgs3(char* arg){
        args3=arg;
    }
    bool isEmpty(){
        if(size==0)return true;
        else return false;
    }
    bool isFull(){
        if(size==capacity)return true;
        else return false;
    }
    void buildPQAry(){
        ifstream reader(args1);
        ofstream writer(args2);
        string s;
        int count=0;
        while(reader >> s){
            int x=atoi(s.c_str());
            insertSingleDataitem(x);
            count++;
            if(count>=10){
            writer<<"Heap so far : \n";
            print(writer,10,true);
            }
        }
        print(writer,10, false);
        reader.close();
        writer.close();
    }
    void insertSingleDataitem(int x){
        if(isFull()==true)throw new runtime_error("full");//not 100% sure how to call exceptions in C++
        else{
            size= ++PQAry[0];
            PQAry[size]=x;
            bubbleUp(size);
        }
    }

    void bubbleUp(int location){
        int father=(location/2);
        while(PQAry[father] > PQAry[location] && father!=0){
            int temp=PQAry[father];
            PQAry[father]=PQAry[location];
            PQAry[location]=temp;
            location=father;
            father=location/2;
        }
    }

    void deleteRoot(){
        if(isEmpty()==true)throw new runtime_error("Empty!");
        ofstream writer(args2, ios::app);
        ofstream writer2(args3);
        writer2<<"Sorted list using heap sort: \n";
        while(!isEmpty()){
        int root=PQAry[1];
        writer2<<root<<" ";
        PQAry[1]=PQAry[size];
        PQAry[size]=root;
        PQAry[size]=0;
        size=--PQAry[0];
        bubbleDown(1);
        if(PQAry[0]!=0){
        writer<<"deleting ("<<root<<")current heap situation :\n";
        print(writer,10,true);
            }
        else{
            writer<<"deleting ("<<root<<")";
            if(isEmpty()==true)
                writer<<" Completely deleted! No more items left!";
            }
        }
        writer.close();
        writer2.close();
    }

    void bubbleDown(int spot){
        int father=spot;
        int leftChild= showLeftChild(father);
        int rightChild= showRightChild(father);
        int minIndex=0;
        if(leftChild > size && rightChild > size){
            return;
        }
        else{
        minIndex=findMinIndex(leftChild, rightChild);
        while(PQAry[father] > PQAry[minIndex] && father <= (size/2)){
                int temp=PQAry[father];
                PQAry[father]=PQAry[minIndex];
                PQAry[minIndex]=temp;
                father=minIndex;
                leftChild=showLeftChild(father);
                rightChild= showRightChild(father);
                minIndex=findMinIndex(leftChild, rightChild);
            }
        }
    }

    int showLeftChild(int father){
        return father*2;
    }
    int showRightChild(int father){
        return (father*2)+1;
    }

    int findMinIndex(int left, int right){
        if(left<= size && right > size)
            return left;
        if(PQAry[left]-PQAry[right]<0)
            return left;
        else
            return right;
    }

    void print(ofstream &out, int limit, bool flag){
        if(flag==true){
        out<<"Printing the heap from 0 to 10 index: \n";
        for(int i=0;i<limit; i++){
            if(PQAry[i]!=0)
            out<<PQAry[i]<<" ";
            }
                    out<<endl;
        }
        else if(flag==false){
            out<<"Final heap: "<<endl;
            for(int i=0;i<capacity;i++){
                    out<<PQAry[i]<<" ";
            }
            out<<endl<<endl;
        }
    }

    ~PQSort(){
        delete []PQAry;
    }


};
int main(int agrc, char* argv[]){
    ifstream findSize;
    findSize.open(argv[1]);
    int customSize=0;
    string s;
    while(findSize >> s){
        customSize++;
    }
    try{
   PQSort newHeap(customSize);
    newHeap.setArgs1(argv[1]);
    newHeap.setArgs2(argv[2]);
    newHeap.setArgs3(argv[3]);
    newHeap.buildPQAry();
    newHeap.deleteRoot();
    }
    catch (exception &e){
        cout<< "exceptions caught!" ;
    }
    findSize.close();
    return 0;
}
