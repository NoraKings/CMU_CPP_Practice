#include <iostream>
using namespace std;

struct MyDynamicArray {
    //we will keep variables private to be able to modify only within the struct

    private:
    static const int MAX_ENTRIES = 1;

    //fixedSizeArray is a pointer that is why the (*)
    int* fixedSizeArray;
    //current capacity of array
    int capacity;
    //no of elements
    int theSize;

    public:
    //Constructor and Destructor
    MyDynamicArray() : fixedSizeArray(new int [MAX_ENTRIES]), theSize(0), capacity(MAX_ENTRIES) {}
    //destructor - cleans up dynammically allocated memory
    ~MyDynamicArray(){
        delete[] fixedSizeArray;
    }

    /////////////////////////////////////////////////Functions to support Dynamic Array ///////////////////////////////////////////
    //check if Dynamic array has no element in it. We use const to indicate it does not modify member variables

    bool empty() const{
        return theSize ==0;
    }

    //return the number of elements in the Dynamic Array
    int size() const{
        return theSize;
    }

    //getter and setters. We use int& when we need the same function to get and set. 
    //It returns a modifiable reference to data [index], so it can be used to modify the element at that specific index

    int& get(int index) {
        if(index >= theSize){
            throw out_of_range("Index out of range.");
        }
        return fixedSizeArray[index];
    }

    //adds elements to end of array (append)

    void addToBack(int value){
        //dynamically expand array if there is no space
        growIfFull();

        //insert element at the end of the Dynamic Array
        fixedSizeArray[theSize++] = value;
    }
    // print size, capacity of dynamic array and also all elements of array

     void printElements() const {
        cout << "In this MyDynamic Array, we have: " <<theSize << "elements.\n";
        cout << "Capacity is: " << capacity << "slots.\n";

        for (int i=0; i < theSize; ++i) {
            cout << fixedSizeArray [i] << " ";
        }
    }

    void removeLastElt() {
        if(theSize == 0){
            throw out_of_range("Cannot delete from an empty array");
            --theSize;
        }
    }

    //Search for an element in Dynamic array and return it's index.
    int find(int elt) const {
        for(int i = 0; i <= theSize; ++i){
            if(fixedSizeArray[i] == elt){
                return i; //return the index of element
            }
            return -1; //Not found
        }
    }

    //remove an element from array at a specific index.
    //thisis implemented by getting that index number and shifting the position of other elements by 1 to replace the value at index we want to remove. And lastly reducing size of array by 1. 
    void removeElement(int elt) {
        int index = find(elt);

        //we are sure element exist before running operations
        if(index != -1) {
            for(int i = index; i < theSize -1; i++){
                fixedSizeArray[i] = fixedSizeArray[i+1];
            }
            --theSize;
        }
        __throw_invalid_argument;
    }



    private:
    //if size of array reaches capacity, dynamically expand
    //obtain a new block of memory, copy old block into the new block and reclaim old block


    void growIfFull(){
        if (theSize >= capacity) {
            int newCapacity = capacity *2;
            int* newfixedSizeArray = new int[newCapacity];

            for(int i=0; i < theSize; ++i) {
                newfixedSizeArray[i] = fixedSizeArray[i];
            }
            capacity = newCapacity;

            delete[] fixedSizeArray;
            fixedSizeArray = newfixedSizeArray;
        }
        
    }

   

};

//testing dynamic array and all functions
int main() {
    //Create a Dynamic Array
    MyDynamicArray dynArray;

    //elements in dynamic array
    dynArray.printElements();

    //add new elements and print after each add
    //size of dyn. array changes as well as capacity doubles every time max capacity reaches

    cout<< "\nAdding new element...\n";
    int num1 = 30;
    dynArray.addToBack(num1);
    dynArray.printElements();

}