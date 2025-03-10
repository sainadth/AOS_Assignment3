#include <bits/stdc++.h>
using namespace std;


/**
 * @brief 
 * 
 * @param numPages 
 * @param maxPageNum 
 * @return vector<int> 
 */
vector<int> generatePages(int numPages, int maxPageNum) {
    vector<int> pages(numPages);
    srand(time(0));
    for (int i = 0; i < numPages; i++) {
        pages[i] = rand() % (maxPageNum + 1);
    }
    return pages;
}

/**
 * @brief FIFO Page Replacement Algorithm
 * 
 * If page found return true
 * else
 *  - Remove the oldest page fomr the queue and set when pageSet is full
 *  - Add the page to the queue and set
 * 
 * @param pageSet 
 * @param pageQueue 
 * @param page 
 * @param capacity 
 * @return true 
 * @return false 
 */

bool FIFO(unordered_set<int>& pageSet, queue<int>& pageQueue, int page, int capacity) {
    if (pageSet.find(page) == pageSet.end()) {
        if (pageSet.size() >= capacity) {
            int oldestPage = pageQueue.front();
            pageQueue.pop();
            pageSet.erase(oldestPage);
        }
        pageQueue.push(page);
        pageSet.insert(page);
        return true;
    }
    return false;
}

/**
 * @brief LRU Page Replacement Algorithm
 * If page is found return true by pushing it to the front of the list
 * 
 * @param pageMap 
 * @param pageList 
 * @param page 
 * @param capacity 
 * @return true 
 * @return false 
 */
bool LRU(unordered_map<int, list<int>::iterator>& pageMap, list<int>& pageList, int page, int capacity) {
    /* 
        The pageMap stores the pageNumber and the pointer iterator the location of the page in the pageList. To efficiently handle the page repealcement of
        the page.
    */
    bool found = false;
    if (pageMap.find(page) == pageMap.end()) {
        if (pageList.size() == capacity) {
            int lruPage = pageList.back();
            pageList.pop_back();
            pageMap.erase(lruPage);
        }
    } else {
        found = true;
        pageList.erase(pageMap[page]);
    }
    pageList.push_front(page);
    pageMap[page] = pageList.begin();
    return found;
}

int main(){
    int numPages = 100;
    int maxPageNum = 1000;
    int capacity = 100;

    vector<int> pages = generatePages(numPages, maxPageNum);

    cout << "Custom Generated Pages: \n";
    for(auto i : pages)
        cout << i << " ";
    cout << endl;

    //FIFO
    unordered_set<int> pageSet;
    queue<int> pageQueue; 

    //LRU
    unordered_map<int, list<int>::iterator> pageMap;
    list<int> pageList;

    for(auto i : pages){
        pageSet.insert(i);
        pageQueue.push(i);

        pageList.push_front(i);
        pageMap[i] = pageList.begin();
    }

    
    int fifo_page_faults = 0;
    int lru_page_faults = 0;
    
    // srand(time(0));
    for(int hits = 1; hits < 1e7; hits *= 10){
        for(int i = 0; i <= hits; i++){
            int page = rand() % (maxPageNum + 1);
            // cout << page << " ";
            if(FIFO(pageSet, pageQueue, page, capacity)) fifo_page_faults++;
            if(LRU(pageMap, pageList, page, capacity)) lru_page_faults++;
        }
        cout << "\nNumber of Hits: " << hits << endl;
        cout << "Page Faults (FIFO): " << fifo_page_faults << endl;
        cout << "Page Faults (LRU): " << lru_page_faults << endl;
        // cout << pageSet.size() << " " << pageQueue.size() << " " << pageMap.size() << " " << pageList.size() << endl;
        cout << "-----------------------------------\n";
    }
}