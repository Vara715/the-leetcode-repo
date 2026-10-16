class BusBooking {
private:
    int n;
    vector<bool> booked;
    vector<int> cost;
    int totalTime = 0;
    int count = 0;

    int findIdx(string seat) {
        char c = seat[0];
        int row = stoi(seat.substr(1)) - 1;

        int col;
        if (c == 'A') {
            col = 0;
        } else if (c == 'B') {
            col = 1;
        } else if (c == 'C') {
            col = 2;
        } else {
            col = 3;
        }

        return row*4 + col;
    }
public:
    BusBooking(int n) {
        this->n = n;
        booked.assign(4*n, false);
        cost.assign(4*n, 0);
    }
    
    void toggle(string seat) {
        int idx = findIdx(seat);
        int col = idx%4;

        if (booked[idx]) {
            booked[idx] = false;
            totalTime -= cost[idx];
            cost[idx] = 0;
            count--;
            return;
        }

        int c= 1;

        if (col == 0 && booked[idx+1]) c=3;
        if (col == 3 && booked[idx-1]) c=3;

        booked[idx] = true;
        totalTime += c;
        cost[idx] = c;
        count++;
    }
    
    int getTotalTime() {
        return totalTime;
    }
    
    int getMinTime() {
        // int ans = 0;

        // for (int i=0; i<4*n; i++) {
        //     if (booked[i]) ans++;
        // }

        // for (int i=0; i<n; i++) {
        //     int tmp = 4*i;

        //     if (booked[tmp] && booked[tmp+1]) ans+=2;
        //     if (booked[tmp+2] && booked[tmp+3]) ans+=2;
        // }

        return count;
    }
};

/**
 * Your BusBooking object will be instantiated and called as such:
 * BusBooking* obj = new BusBooking(n);
 * obj->toggle(seat);
 * int param_2 = obj->getTotalTime();
 * int param_3 = obj->getMinTime();
 */