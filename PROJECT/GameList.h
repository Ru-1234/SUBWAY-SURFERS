#ifndef GAMELIST_H
#define GAMELIST_H

template <typename T>
class GameList {
private:
    T** items; //items stores pointers to dynamically allocated objects t*
    int capacity;
    int size;
    
    void resize() {
        int newCapacity = capacity * 2;
        T** newItems = new T*[newCapacity];
        for (int i = 0; i < size; i++) {
            newItems[i] = items[i];
        }
        delete[] items;
        items = newItems;
        capacity = newCapacity;
    }

public:
    GameList() : capacity(10), size(0) {
        items = new T*[capacity];
    }
    
    ~GameList() {
        for (int i = 0; i < size; i++) {
            delete items[i];
        }
        delete[] items;
    }
    
    void add(T* item) {
        if (size >= capacity) {
            resize();
        }
        items[size++] = item;
    }
    
    T* get(int index) {
        if (index >= 0 && index < size) {
            return items[index];
        }
        return nullptr;
    }
    
    int getSize() const {
        return size;
    }
    
    void removeAt(int index) {
        if (index >= 0 && index < size) {
            delete items[index];
            for (int i = index; i < size - 1; i++) {
                items[i] = items[i + 1];
            }
            size--;
        }
    }
    
    void clear() {
        for (int i = 0; i < size; i++) {
            delete items[i];
            items[i] = nullptr;
        }
        size = 0;
    }
};

#endif
