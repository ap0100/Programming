#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>
#include <iomanip>
#include <tuple>
using namespace std;

//-----------------Min Rastojanie Megu N tochki, 2D-------------------
/*
//sekade vo funkciite se raboti so kvadratot od rastojanieto, na kraj vo main samo se zema korenot
int calculate_distance_2(pair<int, int> &x, pair<int, int> &y) {
    int dx=x.first-y.first;
    int dy=x.second-y.second;
    return dx*dx+dy*dy;
}

int split(vector<pair<int, int>> &P) {
    if (P.size()<=3) {
        int d=INT_MAX;
        for (int i=0; i<P.size()-1; i++) {
            for (int j=i+1; j<P.size(); j++)
                d=min(calculate_distance_2(P[i],P[j]), d);
        }
        return d;
    }

    int mid=P.size()/2;
    vector<pair<int, int>> leftP, rightP;

    for (int i=0; i<mid; i++) leftP.push_back(P[i]);
    for (int i=mid; i<P.size(); i++) rightP.push_back(P[i]);

    int dl=split(leftP);
    int dr=split(rightP);

    return min(dl, dr);
}

int merge_2d(vector<pair<int, int>> &arr, int l, int r, int m) {
    vector<pair<int, int>> P1, P2;

    for (int i=l; i<=m; i++) P1.push_back(arr[i]);
    for (int j=m+1; j<=r; j++) P2.push_back(arr[j]);

    int d=min(split(P1), split(P2));
    //sega treba od sredina na arr da gi gleda tochkite shto se d rastojanie levo i desno
    int divide_x=arr[m].first, dx;
    vector<pair<int, int>> strip;

    for (int i=l; i<=r; i++) {
        dx=arr[i].first-divide_x;
        if (dx*dx < d) strip.push_back(arr[i]);
    }

    sort(strip.begin(), strip.end(), [](const pair<int, int> &a , const pair<int, int> &b) {
        return a.second<b.second;
    });

    for (int i=0; i<strip.size()-1; i++) {
        for (int j=i+1; j<strip.size(); j++) {
            int dy=strip[j].second-strip[i].second;
            if (dy*dy<d) d=min(d, calculate_distance_2(strip[i], strip[j]));
        }
    }

    return d;
}
*/


//-----------------Min Rastojanie Megu N tochki, 3D-------------------

int calculate_distance_2(tuple<int, int, int> &a, tuple<int, int, int> &b) {
    int dx=get<0>(a)-get<0>(b);
    int dy=get<1>(a)-get<1>(b);
    int dz=get<2>(a)-get<2>(b);
    return dx*dx+dy*dy+dz*dz;
}

int split(vector<tuple<int, int, int>> &P) {
    if (P.size()<=3) {
        int d=INT_MAX;
        for (int i=0; i<P.size()-1; i++) {
            for (int j=i+1; j<P.size(); j++)
                d=min(calculate_distance_2(P[i],P[j]), d);
        }
        return d;
    }

    int mid=P.size()/2;
    vector<tuple<int, int, int>> leftP, rightP;

    for (int i=0; i<mid; i++) leftP.push_back(P[i]);
    for (int i=mid; i<P.size(); i++) rightP.push_back(P[i]);

    int dl=split(leftP);
    int dr=split(rightP);

    return min(dl, dr);
}

int merge_3d(vector<tuple<int, int, int>> &arr, int l, int r, int m) {
    vector<tuple<int, int, int>> P1, P2;

    for (int i=l; i<=m; i++) P1.push_back(arr[i]);
    for (int j=m+1; j<=r; j++) P2.push_back(arr[j]);

    int d=min(split(P1), split(P2));

    int divide_x=get<0>(arr[m]), dx;
    vector<tuple<int, int, int>> strip;

    for (int i=l; i<=r; i++) {
        dx=get<0>(arr[i])-divide_x;
        if (dx*dx < d) strip.push_back(arr[i]);
    }

    sort(strip.begin(), strip.end(), [](const tuple<int, int, int> &a , const tuple<int, int, int> &b) {
       return get<1>(a)<get<1>(b);
    });

    for (int i=0; i<strip.size()-1; i++) {
        for (int j=i+1; j<strip.size(); j++) {
            int dy=get<1>(strip[j])-get<1>(strip[i]);
            int dz=get<2>(strip[j])-get<2>(strip[i]);
            if (dy*dy<d && dz*dz<d) d=min(d, calculate_distance_2(strip[i], strip[j]));
        }
    }

    return d;
}


int main() {
    //----------------------------Ideja-------------------------------------------------
    //dadeni se N tochki vo 2D prostor, se bara min rastojanie shto se javuva megu nekoi dve tochki od site tie N
    //se sortiraa tochkite po x koordinata
    //se deli ramninata na dva dela/prostora P1 i P2
    //se prodolzuva so delenje na sekoj od prostorite na po pola i koga kje ostanat <=3 od tri tochki, se naoga min rastojanie megu niv i toa e di za cel Pi prostor
    //d=min(d1, d2)
    //kaj shto e granicata (kaj shto sme go podelile prostorot na dva), se odereduva rastojanie d levo i desno od granicata

    //-----------------------------------------------------------------------------

    /*
    int N, x, y;
    vector<pair<int, int>> points;

    cin >> N;
    for (int i=0; i<N; i++) {
        cin >> x >> y;
        points.push_back({x, y});
    }
    sort(points.begin(), points.end());

    cout << fixed <<  setprecision(4) << sqrt(merge_2d(points, 0, N-1, (N-1)/2));
    */

    //-----------------------------------------------------------------------------

    int N, x, y, z;
    vector<tuple<int, int, int>> points;

    cin >> N;
    for (int i=0; i<N; i++) {
        cin >> x >> y >> z;
        points.push_back({x, y, z});
    }
    sort(points.begin(), points.end());

    cout << fixed << setprecision(4) << sqrt(merge_3d(points, 0, N-1, (N-1)/2));


    return 0;
}