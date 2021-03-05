#ifndef MARKER_PUBLISHER_HPP
#define MARKER_PUBLISHER_HPP

#include <iostream>
#include <fstream>
#include <vector>

// #include <g2o/core/factory.h>
#include <iomanip>
#include <Eigen/StdVector>

#include <ros/ros.h>
#include <geometry_msgs/Point.h>
#include <visualization_msgs/MarkerArray.h>



class MarkerPublisher
{
	public:
		MarkerPublisher(){};
		~MarkerPublisher(){};
		void markerPoints(visualization_msgs::MarkerArray _marker, std::vector<geometry_msgs::Point> _vector, int _suffix, int _n_v, ros::Publisher c_m_pub_);
		void clearMarkers(visualization_msgs::MarkerArray _marker, auto _s, ros::Publisher c_m_pub_);
		void getMarkerPoints(visualization_msgs::MarkerArray &marker_, std::vector<Eigen::Vector3d> _vector, std::string ns, int colour_);
		void getMarkerLines(visualization_msgs::MarkerArray &marker_, std::vector<Eigen::Vector3d> _vector, std::string ns, int colour_);
		void clearMarkersPointLines(visualization_msgs::MarkerArray &p_m_, visualization_msgs::MarkerArray &l_m_, ros::Publisher traj_m_pub_, auto _s);

	protected:

	private:

};


inline void MarkerPublisher::markerPoints(visualization_msgs::MarkerArray _marker, std::vector<geometry_msgs::Point> _vector, int _suffix, int _n_v, ros::Publisher c_m_pub_)
{
    std::string string_marker;
    std::string ns_marker;

    double c_color1 = (_suffix / (double)_n_v)*0.5;
    double c_color2 = (_suffix / (double)_n_v)*0.5;
    double c_color3;
    if (_suffix%2 == 0)
        c_color3 = 0.5;
    else
        c_color3 = 0.0;
            
    string_marker = std::to_string(_suffix);
    ns_marker = "catenary_"+string_marker;

    _marker.markers.resize(_vector.size());
            
    for (size_t i = 0; i < _vector.size(); ++i){
        _marker.markers[i].header.frame_id = "/map";
        _marker.markers[i].header.stamp = ros::Time::now();
        _marker.markers[i].ns = ns_marker;
        _marker.markers[i].id = i+1;
        _marker.markers[i].action = visualization_msgs::Marker::ADD;
        if (i % 5 == 0)
            _marker.markers[i].type = visualization_msgs::Marker::CUBE;
        else
            _marker.markers[i].type = visualization_msgs::Marker::SPHERE;
        _marker.markers[i].lifetime = ros::Duration(400);
        _marker.markers[i].pose.position.x = _vector[i].x; 
        _marker.markers[i].pose.position.y = _vector[i].y; 
        _marker.markers[i].pose.position.z = _vector[i].z;

        _marker.markers[i].pose.orientation.x = 0.0;
        _marker.markers[i].pose.orientation.y = 0.0;
        _marker.markers[i].pose.orientation.z = 0.0;
        _marker.markers[i].pose.orientation.w = 1.0;
        _marker.markers[i].scale.x = 0.06;
        _marker.markers[i].scale.y = 0.06;
        _marker.markers[i].scale.z = 0.06;
        _marker.markers[i].color.a = 1.0;
        _marker.markers[i].color.r = 1.0 - c_color1;
        _marker.markers[i].color.g = c_color2;
        _marker.markers[i].color.b = c_color3;
    }	
    c_m_pub_.publish(_marker);
}

inline void MarkerPublisher::clearMarkers(visualization_msgs::MarkerArray _marker, auto _s, ros::Publisher c_m_pub_)
{
    _marker.markers.clear();
    _marker.markers.resize(_s);

    for (auto i = 0 ; i < _s; i++){
        _marker.markers[i].action = visualization_msgs::Marker::DELETEALL;
    }
    c_m_pub_.publish(_marker);
}

inline void MarkerPublisher::getMarkerPoints(visualization_msgs::MarkerArray &marker_, std::vector<Eigen::Vector3d> vector_, std::string ns_, int colour_)
{
	// RED: colour_ = 0 ; GREEN : colour_ = 1 ; BLUE: colour_ = 2
	for (size_t i = 0; i < vector_.size(); i++){
		marker_.markers[i].header.frame_id = "/map";
		marker_.markers[i].header.stamp = ros::Time::now();
		marker_.markers[i].ns = ns_;
		marker_.markers[i].id = i+1;
		marker_.markers[i].action = visualization_msgs::Marker::ADD;
		if (i % 5 == 0)
			marker_.markers[i].type = visualization_msgs::Marker::CUBE;
		else
			marker_.markers[i].type = visualization_msgs::Marker::SPHERE;
		marker_.markers[i].lifetime = ros::Duration(400);
		marker_.markers[i].pose.position.x = vector_[i].x();
		marker_.markers[i].pose.position.y = vector_[i].y();
		marker_.markers[i].pose.position.z = vector_[i].z();
		marker_.markers[i].pose.orientation.x = 0.0;
		marker_.markers[i].pose.orientation.y = 0.0;
		marker_.markers[i].pose.orientation.z = 0.0;
		marker_.markers[i].pose.orientation.w = 1.0;
		marker_.markers[i].scale.x = 0.2;
		marker_.markers[i].scale.y = 0.2;
		marker_.markers[i].scale.z = 0.2;
		marker_.markers[i].color.a = 1.0;
		if (colour_ == 0){
			marker_.markers[i].color.r = 0.9;
			marker_.markers[i].color.g = 0.0;
			marker_.markers[i].color.b = 0.0;
		}
		if (colour_ == 1){
			marker_.markers[i].color.r = 0.0;
			marker_.markers[i].color.g = 0.9;
			marker_.markers[i].color.b = 0.0;
		}
		if (colour_ == 2){
			marker_.markers[i].color.r = 0.9;
			marker_.markers[i].color.g = 0.0;
			marker_.markers[i].color.b = 0.9;
		}
	}	
}

inline void MarkerPublisher::getMarkerLines(visualization_msgs::MarkerArray &marker_, std::vector<Eigen::Vector3d> _vector, std::string ns_, int colour_)
{
	// RED: colour_ = 0 ; GREEN : colour_ = 1 ; BLUE: colour_ = 2
	for (size_t i = 0; i < _vector.size()-1; i++){
		geometry_msgs::Point _p1, _p2; 
		marker_.markers[i].header.frame_id = "/map";
		marker_.markers[i].header.stamp = ros::Time::now();
		marker_.markers[i].ns = ns_;
		marker_.markers[i].id = i + _vector.size()+2;
		marker_.markers[i].action = visualization_msgs::Marker::ADD;
		marker_.markers[i].type = visualization_msgs::Marker::LINE_STRIP;
		marker_.markers[i].lifetime = ros::Duration(400);
		_p1.x = _vector[i].x();
		_p1.y = _vector[i].y();
		_p1.z = _vector[i].z();
		marker_.markers[i].points.push_back(_p1);
		_p2.x = _vector[i+1].x();
		_p2.y = _vector[i+1].y();
		_p2.z = _vector[i+1].z();
		marker_.markers[i].points.push_back(_p2);
		marker_.markers[i].pose.orientation.x = 0.0;
		marker_.markers[i].pose.orientation.y = 0.0;
		marker_.markers[i].pose.orientation.z = 0.0;
		marker_.markers[i].pose.orientation.w = 1.0;
		marker_.markers[i].scale.x = 0.1;
		// marker_.markers[i].scale.y = 0.3;
		// marker_.markers[i].scale.z = 0.1;
		marker_.markers[i].color.a = 1.0;
		if (colour_ == 0){
			marker_.markers[i].color.r = 0.9;
			marker_.markers[i].color.g = 0.0;
			marker_.markers[i].color.b = 0.9;
		}
		if (colour_ == 1){
			marker_.markers[i].color.r = 0.0;
			marker_.markers[i].color.g = 0.9;
			marker_.markers[i].color.b = 0.0;
		}
		if (colour_ == 2){
			marker_.markers[i].color.r = 0.0;
			marker_.markers[i].color.g = 0.0;
			marker_.markers[i].color.b = 0.9;
		}
	}
}

void MarkerPublisher::clearMarkersPointLines(visualization_msgs::MarkerArray &p_m_, visualization_msgs::MarkerArray &l_m_, ros::Publisher traj_m_pub_, auto _s)
{
	l_m_.markers.clear();
	p_m_.markers.clear();

	l_m_.markers.resize(_s);
	p_m_.markers.resize(_s);

	for (auto i = 0 ; i < _s; i++){
		p_m_.markers[i].action = visualization_msgs::Marker::DELETEALL;
		l_m_.markers[i].action = visualization_msgs::Marker::DELETEALL;
	}
	traj_m_pub_.publish(p_m_);
	traj_m_pub_.publish(l_m_);
}

#endif