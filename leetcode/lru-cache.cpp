class LRUCache {
public:
    class Node {
        public:
            int key, val;
            Node* next;
            Node* prev;

            Node(int k, int v){
                key = k;
                val = v;

                next = prev = nullptr;
            }
    };

    Node* head = new Node(-1, -1);
    Node* tail = new Node(-1, -1);
    unordered_map<int, Node*> mp;

    int limit = 0;

    void addNode(Node* newNode) {
        Node* oldNext = head->next;
        head->next = newNode;
        oldNext->prev = newNode;
        newNode->prev = head;
        newNode->next = oldNext;
    }

    void delNode(Node* oldNode) {
        Node* oldPrev = oldNode->prev;
        Node* oldNext = oldNode->next;

        oldPrev->next = oldNext;
        oldNext->prev = oldPrev;
    }

    LRUCache(int capacity) {
        limit = capacity;
        head->next = tail;
        tail->prev = head;
    }
    
    int get(int key) {
        if (mp.find(key) == mp.end()) {
            return -1;
        }

        Node* node = mp[key];
        delNode(node);
        addNode(node);
        return node->val;
    }
    
    void put(int key, int value) {
        //if node already exits
        if (mp.find(key) != mp.end()) {
            Node* node = mp[key];
            delNode(node);
            mp.erase(key);
        }

        //if size full
        if (mp.size() >= limit) {
            int key = tail->prev->key;
            delNode(tail->prev);
            mp.erase(key);
        }

        Node* newNode = new Node(key, value);
        addNode(newNode);
        mp[key] = newNode;
    }

    ~LRUCache() {
        Node* curr = head;
        while (curr) {
            Node* next = curr->next;
            delete curr;
            curr = next;
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */