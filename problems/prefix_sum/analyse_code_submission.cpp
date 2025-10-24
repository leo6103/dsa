#include <bits/stdc++.h>
using namespace std;

#define fast_io ios::sync_with_stdio(false); cin.tie(nullptr);
/**
 * Range t1 to t2 include job summited at both t1 and t2
 */
int time_series[864001];

//HH:MM:SS
int time_to_int(string time) {
  return ((time[0] - '0') * 10 + (time[1] - '0')) * 3600 + ((time[3] - '0') * 10 + (time[4] - '0')) * 60 +  (time[6] - '0') * 10 + (time[7] - '0');
}

int main () {
  fast_io;
  //
  int total_sub = 0, total_err_sub = 0;
  unordered_map<string, int> err_uid, user_point, point_map;
  // point map 2D vecto
  vector<vector<string>> timecount;

  string uid, pid, time, status, query;
  int point;

  while (1) {
    cin >> uid;
    if (uid == "#") break;
    cin >> pid >> time >> status >> point;
    total_sub ++;
    string point_key = uid + pid;
    time_series[time_to_int(time)] ++;
    if (status == "OK" && point > point_map[point_key]) {
      point_map[point_key] = point; 
      user_point[uid] += point;
    }
    if (status == "ERR") {
      total_err_sub ++;
      err_uid[uid] ++;
    }
  }
  
  int prefix_sum = 0;
  for (int i = 0; i <= 864000; ++i) {
    if (time_series[i] != 0) {
      time_series[i] += prefix_sum;
      prefix_sum = time_series[i];
    } else {
      time_series[i] = prefix_sum;
    }
  }

  while (1) {
    cin >> query;
    if (query == "#") break;
    else if (query == "?total_number_submissions") {
      cout << total_sub << endl;
    } else if (query == "?number_error_submision") {
      cout << total_err_sub << endl;
    } else if (query == "?number_error_submision_of_user") {
      string quid;
      cin >> quid;
      cout << err_uid[quid] << endl;
    } else if (query == "?total_point_of_user") {
      string quid;
      cin >> quid;
      cout << user_point[quid] << endl;
    } else if (query == "?number_submission_period") {
      string start, end;
      cin >> start >> end;
      int start_int = time_to_int(start);
      int end_int = time_to_int(end);
    
      cout << time_series[end_int] - time_series[start_int - 1]<< endl;
    }
  }

  return 0;
}