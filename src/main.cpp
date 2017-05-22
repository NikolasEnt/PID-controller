#include <uWS/uWS.h>
#include <iostream>
#include "json.hpp"
#include "PID.h"
#include <math.h>

// for convenience
using json = nlohmann::json;
using namespace std;

// For converting back and forth between radians and degrees.
constexpr double pi() { return M_PI; }
double deg2rad(double x) { return x * pi() / 180; }
double rad2deg(double x) { return x * 180 / pi(); }

// Checks if the SocketIO event has JSON data.
// If there is data the JSON object in string format will be returned,
// else the empty string "" will be returned.
std::string hasData(std::string s) {
  auto found_null = s.find("null");
  auto b1 = s.find_first_of("[");
  auto b2 = s.find_last_of("]");
  if (found_null != std::string::npos) {
    return "";
  }
  else if (b1 != std::string::npos && b2 != std::string::npos) {
    return s.substr(b1, b2 - b1 + 1);
  }
  return "";
}





int main()
{
  uWS::Hub h;

  PID pid;
  
  double c_time = 0.0; //Current time
  double p_time = clock(); //Prev time 
  double t = 0.0;
  // TODO: Initialize the pid variable.
  // TODO: Tweak initial Kp, Ki, Kd values.
  //pid.Init(0.04, 0.0, 0.03);
  pid.Init(0.1, 0.25, 0.03); 
  //pid.Init(0.075, 0.25, 0.01); 
  //pid.Init(0.075, 0, 0.01); 0.4
  //pid.Init(0.1, 0.25, 0.008); 0.3
  
  h.onMessage([&pid, &c_time, &p_time, &t](uWS::WebSocket<uWS::SERVER> ws, char *data, size_t length, uWS::OpCode opCode) {
    //"42" at the start of the message means there's a websocket message event.
    //The 4 signifies a websocket message
    //The 2 signifies a websocket event
    if (length && length > 2 && data[0] == '4' && data[1] == '2')
    {
      auto s = hasData(std::string(data));
      if (s != "") {
        auto j = json::parse(s);
        string event = j[0].get<string>();
        if (event == "telemetry") {
          // j[1] is the data JSON object
          double cte = stod(j[1]["cte"].get<string>());
          double speed = stod(j[1]["speed"].get<string>());
          double angle = stod(j[1]["steering_angle"].get<string>());
          double steer_value;
          /*
          * TODO: Calcuate steering value here, remember the steering value is
          * [-1, 1].
          * NOTE: Feel free to play around with the throttle and speed. Maybe use
          * another PID controller to control the speed!
          */
          
          c_time = clock();
          double dt = (c_time - p_time) / CLOCKS_PER_SEC;
          pid.UpdateError(cte, dt);
          //cout << "dt: " << (c_time - p_time) / CLOCKS_PER_SEC << "\n";
          steer_value = -pid.TotalError(speed);
          //std::cout << "Steer: " << steer_value << std::endl;
          if (steer_value > 1) {
            steer_value = 1;
          }
          else if (steer_value < -1) {
            steer_value = -1;
          }
          
          //if (fabs(cte)<0.3){
			  //steer_value = 0.0;
		  //}
          // Smoothing of steering angle
          //steer_value = 0.6 * angle / 25 + 0.4 * steer_value;
          // DEBUG
          //cout << "CTE: " << cte << " Steering Value: " << steer_value << std::endl;
          
          // Set throttle
          double thr = 0.4;
          if (fabs(pid.p_error - cte) > 0.1 and fabs(pid.p_error - cte) <= 0.2){
			  thr = 0.0;
		  }
		  else if (fabs(pid.p_error - cte) > 0.2){
			  thr = -0.2; // Break!
		  }
          json msgJson;
          msgJson["steering_angle"] = steer_value;
          msgJson["throttle"] = thr;
          auto msg = "42[\"steer\"," + msgJson.dump() + "]";
          ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
          // DEBUG output
          t += dt;
          cout << t << ";" << cte << ";" << speed << ";" << angle << ";" << steer_value * 25.0 << ";\n";
          p_time = c_time;
        }
      } else {
        // Manual driving
        std::string msg = "42[\"manual\",{}]";
        ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
      }  
    }
    
  });

   //We don't need this since we're not using HTTP but if it's removed the program
  // doesn't compile :-(
  h.onHttpRequest([](uWS::HttpResponse *res, uWS::HttpRequest req, char *data, size_t, size_t) {
    const string s = "<h1>Hello world!</h1>";
    if (req.getUrl().valueLength == 1)
    {
      res->end(s.data(), s.length());
    }
    else
    {
      // i guess this should be done more gracefully?
      res->end(nullptr, 0);
    }
  });

  h.onConnection([&h](uWS::WebSocket<uWS::SERVER> ws, uWS::HttpRequest req) {
    std::cout << "Connected!!!" << std::endl;
  });

  h.onDisconnection([&h](uWS::WebSocket<uWS::SERVER> ws, int code, char *message, size_t length) {
    ws.close();
    std::cout << "Disconnected" << std::endl;
  });

  int port = 4567;
  if (h.listen(port))
  {
    std::cout << "Listening to port " << port << std::endl;
  }
  else
  {
    std::cerr << "Failed to listen to port" << std::endl;
    return -1;
  }
  std::cout << "HELLO\n";
  h.run();
}
