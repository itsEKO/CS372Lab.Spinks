#include <iostream>
template <typename T>
class Vector {
public:
  void vector::put(T data, int pos) {
  if (index == vCapacity) {
    push_back(T data);
  }
  else {
    arr[index] = data;
  }
}
  void push_back(T data)
    {
        // if number of elements is equal to capacity
        // than we need to reallocate and deep copy
        if (length == vCapacity) {
            expand(2 * vCapacity);
        }
        arr[length] = data;
        length++;
    }
  T &at(int index) {
        if (index < 0 || index > length) {
            std::cerr << "Vector: index out of bounds on access" << std::endl;
            exit(1);
        }
        else {
            return arr[index];
        }
    } 
    int size() {
        return length;
    }
    int capacity()
    {
        return vCapacity;
    }
  void traverse() {
        for (int i = 0; i < length; i++) {
            cout << arr[i] << endl;
        }
        cout << endl;
    }
  void expand(int newCapacity) {
  if (newCapacity > vCapacity) {
    T *temp = new T[newCapacity];
    for (int i = 0; i < length; i++) {
      temp[i] = arr[i];
    }
    delete[] arr;
    vCapacity = newCapacity;
    arr = temp;
  }
  else {
    std::cerr << "vector::expand: new capacity is less than equal to current\n";
  }
}
private:
  T *arr = new T[1];
  int vCapacity = 1;
  int length = 0;
};