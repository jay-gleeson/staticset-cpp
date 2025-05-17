#ifndef STATICSET_H
#define STATICSET_H

#include <functional>
#include <iostream>
#include <unordered_set>
#include <vector>

template <typename T>
class StaticSet {
private:
   std::unordered_set<T> set;

public:
   // Constructs an empty StaticSet
   StaticSet() {
   }

   // Constructs the StaticSet by adding all vector items
   StaticSet(const std::vector<T>& items) {
      for (const T& item : items) {
         set.insert(item);
      }
   }
   
   // Constructs the StaticSet by copying itemsToCopy's items
   StaticSet(const std::unordered_set<T>& itemsToCopy) : set(itemsToCopy) {
   }
   
   virtual ~StaticSet() {
   }
   
   bool Contains(const T& item) const {
      return 1 == set.count(item);
   }
   
   int GetSize() const {
      return (int) set.size();
   }
   
   void Print(std::ostream& output, std::string separator,
      std::string prefix="", std::string suffix="") const {
      output << prefix;
      bool firstItem = true;
      for (const T& item : set) {
         if (firstItem) {
            output << item;
            firstItem = false;
         }
         else {
            output << separator << item;
         }
      }
      output << suffix;
   }
   
   // Returns a StaticSet<T> containing each element from this set that is not
   // in otherSet.
   StaticSet<T> Difference(const StaticSet& otherSet) const {
      /*
      SetDifference(set1, set2) {
         result = Create new, empty set
         for each (element in set1) {
            if (SetSearch(set2, element⇢key) == null) {
               Add element to result
            }
         }
         return result
      }
      */
      
      std::unordered_set<T> result;
      for (auto i : this->set) {
         if (!otherSet.Contains(i)) {
            result.insert(i);
         }
      }
      
      return StaticSet<T>(result);
   }
   
   // Returns a StaticSet<T> containing each element from this set that
   // satisfies the predicate.
   // - If predicate(item) returns true, item satisfies the predicate.
   // - If predicate(item) returns false, item does not satisfy the predicate.
   StaticSet<T> Filter(std::function<bool(const T&)> predicate) const {
      /*
      SetFilter(set, predicate) {
         result = Create a new, empty set
         for each (element in set) {
            if (predicate(element) == true)
               Add element to result
         }
         return result
      }
      */
      
      std::unordered_set<T> result;
      for (auto i : this->set) {
         if (predicate(i)) {
            result.insert(i);
         }
      }
      
      return StaticSet<T>(result);
   }
   
   // Returns a StaticSet<T> containing each element from this set that is also
   // in otherSet.
   StaticSet<T> Intersection(const StaticSet& otherSet) const {
      /* 
      SetIntersection(set1, set2) {
         result = Create new, empty set
         for each (element in set1) {
            if (SetSearch(set2, element⇢key) != null) {
               Add element to result
            }
         }
         return result
      }
      */
      
      std::unordered_set<T> result;
      for (auto i : this->set) {
         if (otherSet.Contains(i)) {
            result.insert(i);
         }
      }
      
      return StaticSet<T>(result);
   }
   
   // Calls mapFunction(item) for each item in this set and adds the returned
   // item to a StaticSet<U>. After mapFunction has been called for each item
   // in this set, the StaticSet<U> object is returned.
   template <typename U>
   StaticSet<U> Map(std::function<U(const T&)> mapFunction) const {
      /*
      SetMap(set, mapFunction) {
         result = Create new, empty set
         for each (element in set) {
            newElement = mapFunction(element)
            Add newElement to result
         }
         return result
      }
      */
      
      std::unordered_set<U> result;
      for (auto i : this->set) {
         result.insert(mapFunction(i));
      }
      
      return StaticSet<U>(result);
   }
   
   // Returns a StaticSet<T> containing every element from this set and every
   // element from otherSet.
   StaticSet<T> Union(const StaticSet& otherSet) const {
      /* 
      SetUnion(set1, set2) {
         result = Create new, empty set
         for each (element in set1) {
            Add element to result
         }
         for each (element in set2) {
            Add element to result
         }
         return result
      }
      */
      
      std::unordered_set<T> result = this->set;
      for (auto i : otherSet.set) {
         if (!(this->Contains(i))) {
            result.insert(i);
         }
      }
      
      return StaticSet<T>(result);
   }
};

#endif