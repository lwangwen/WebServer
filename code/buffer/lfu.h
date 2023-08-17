#include <list>
#include <string>
#include <unordered_map>
#include <sys/mman.h>

using namespace std;

struct Node {
    int freq;
    void* val;
    string key;
    string md5;
    size_t size;
    Node(string _key, string _md5, size_t _size, int* _val, int _freq) : key(_key), md5(_md5), size(_size), val(_val), freq(_freq) {}
};

class LFUCache {
public:
    int _cache, minFreq;  
    unordered_map<int, list<Node>> freqTolist;
    unordered_map<string, list<Node>::iterator> map;
    bool flag = false;
    LFUCache(int capacity) {
        minFreq = 1;
        _cache = capacity;
    }

    void* get(string key, string md5) {
        if(!map.count(key)) {
            return nullptr;
        }
        if (map[key]->md5 != md5) {
            delfromFreqList(map[key]);
            map.erase(key);
            return nullptr;
        }
        auto node = map[key];
        int freq = node->freq;
        void* val = node->val;
        szie_t sz = node->size;
        // 先在原有频率的链表中删除节点
        delfromFreqList(map[key]);
        freqTolist[freq+1].push_front(Node(key, md5, sz, val, freq + 1));
        map[key] = freqTolist[freq+1].begin();
        return val;
    }
    
    void put(string key, string md5, void* value, size_t sz) {
        if(_cache == 0) return;
        // 判断是否已经存在  
        if(map.count(key)) {
            auto node = map[key];    
            int freq = node->freq;
            // 在原有频率的链表中删除节点
            freqTolist[freq].erase(node);
            if(freqTolist[freq].size() == 0) {
                freqTolist.erase(freq);
                if(minFreq == freq) minFreq++;
            }
            freqTolist[freq+1].push_front(Node(key, md5, sz, value, freq + 1));
            map[key] = freqTolist[freq+1].begin();
        }
        else {
            if(map.size() == _cache) {
                auto it = freqTolist[minFreq].back();
                void* fd = map[it.key]->val;
                int size = map[it.key]->size;
                map.erase(it.key);
                freqTolist[minFreq].pop_back();
                unmap(fd, size);
                if(freqTolist[minFreq].size() == 0) {
                    freqTolist.erase(minFreq);
                }
            }
            freqTolist[1].push_front(Node(key, md5, sz, value, 1));
            map[key] = freqTolist[1].begin();
            minFreq = 1;
        }
    }
private:
    void delfromFreqList(list<Node>::iterator node) {
        int freq = node->freq;
        freqTolist[freq].erase(node);
        if (freqTolist[freq].size() == 0) {
            freqTolist.erase(freq);
        }
        unmap(node->val, node->size);
    }

    void unmap(int* fd, size_t size) {
        munmap(fd, size);
    }

};

