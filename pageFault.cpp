#include <bits/stdc++.h>
using namespace std;


/**
 * @brief 
 * randomly generates pages for the simulation
 * randomly generates pages for the simulation
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
 * If page found return false
 * else
 *  - Remove the oldest page fomr the queue and set when pageSet is full
 *  - Add the page to the queue and set
 *  - return true since it is a page fault
 * 
 * @param pageSet 
 * @param pageQueue 
 * @param page 
 * @param capacity 
 * @return true 
 * @return false 
 */

bool FIFO(unordered_set<int>& pageSet, queue<int>& pageQueue, int page, int capacity) {
    /* 
        pageSet stores distinct pages in the memory
        pageQueue stores the order of pages in the memory
    */
    /* 
        pageSet stores distinct pages in the memory
        pageQueue stores the order of pages in the memory
    */
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
 * If page is found return false by pushing it to the front of the list
 * else push page to front and return true since it is a page fault
 * If page is found return false by pushing it to the front of the list
 * else push page to front and return true since it is a page fault
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
        The pageMap stores the pageNumber and the iterator to the latest location of the page in the pageList.
        The pageList stores the order of pages in the memory
        The pageMap stores the pageNumber and the iterator to the latest location of the page in the pageList.
        The pageList stores the order of pages in the memory
    */
    bool found = false;
    if (pageMap.find(page) == pageMap.end()) {
        if (pageList.size() == capacity) {
            int lruPage = pageList.back();
            pageList.pop_back();
            pageMap.erase(lruPage);
        }
    } else {
        /* Ate around 2hrs in debugging, I'll remember you for the rest of the semester mister pageList */
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
    int capacity = 200;

    vector<int> pages = generatePages(numPages, maxPageNum);

    cout << "My Custom Generated Pages: \n";
    for(auto i : pages)
        cout << i << " ";
    cout << endl;

    //FIFO setup
    //FIFO setup
    unordered_set<int> pageSet;
    queue<int> pageQueue; 

    //LRU setup
    //LRU setup
    unordered_map<int, list<int>::iterator> pageMap;
    list<int> pageList;

    /* 
        Initialize the memory with the generated pages for both LRU and FIFO
    */
    /* 
        Initialize the memory with the generated pages for both LRU and FIFO
    */
    for(auto i : pages){
        pageSet.insert(i);
        pageQueue.push(i);

        pageList.push_front(i);
        pageMap[i] = pageList.begin();
    }

    
    int fifo_page_faults = 0;
    int lru_page_faults = 0;
    
    // srand(time(0));
    /* 
        page_access are increased by a factor of 10 each iteration
    */
    for(int page_access = 1; page_access < INT_MAX; page_access *= 10){
        for(int i = 0; i <= page_access; i++){
            /* Selecting a random page for accessing */
            int page = rand() % (maxPageNum + 1);

            /* check page fault for FIFO */
            if(FIFO(pageSet, pageQueue, page, capacity)) fifo_page_faults++;
            
            /* check page fault for LRU */
            if(LRU(pageMap, pageList, page, capacity)) lru_page_faults++;
        }
        cout << "\nNumber of page_access: " << page_access << endl;
        cout << "\nNumber of page_access: " << page_access << endl;
        cout << "Page Faults (FIFO): " << fifo_page_faults << endl;
        cout << "Page Faults (LRU): " << lru_page_faults << endl;
        // cout << pageSet.size() << " " << pageQueue.size() << " " << pageMap.size() << " " << pageList.size() << endl;
        cout << "-----------------------------------\n";
    }
}