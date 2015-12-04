#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include <vector>
#include <algorithm>
#include "Object.h"
#include "Learn.h"

class ObjectManager {
 public:
  static ObjectManager * getInstance() {
    if (p == NULL) {
      p = new ObjectManager();
    }
    return p;
  }
  ~ObjectManager() {
    for (int i = 0; i < list.size(); ++i) {
      delete list[i];
    }
    list.clear();

    delete p;
  }

  void insert(Object*);
  void remove(Object*);
  void clear();
  bool execute();
  void draw();
  int size() { return list.size(); }

  Object* getObject(int n) { return list[n]; }

  std::vector< Object* > getList() const { return list; }
  Learn& learn() { return learn_; }

 private:
  static ObjectManager * p;
  std::vector< Object*  > list;
  Learn learn_;

  ObjectManager() {}
  void collision();
};

#endif
