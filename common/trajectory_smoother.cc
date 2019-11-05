#include "trajectory_smoother.h"

namespace kamaz {
namespace hagen {
            void TrajectorySmoother::set_smoother(std::string name){
                if(name == "bspline"){
                    _curve = new BSpline();
                }else if(name == "catmull"){
                   _curve = new CatmullRom();
                }
		else if(name == "bezier"){
                   _curve = new Bezier();
                }
            }

            void TrajectorySmoother::clear_smoother(){
                _curve->clear();
            }

            void TrajectorySmoother::set_waypoints(std::vector<Eigen::VectorXf> waypoints, int _number_of_steps){
                 number_of_steps = _number_of_steps;
                _curve->clear();
                // std::cout<<"=====================31========================"<< std::endl;

                _curve->set_steps(waypoints.size()+number_of_steps);
                // std::cout<<"=====================32========================"<< std::endl;

                _curve->add_way_point(Vector(waypoints[0][0], waypoints[0][1], waypoints[0][2]));
                // std::cout<<"=====================33========================"<< std::endl;
                // std::cout<< waypoints.size() << std::endl;
                // int count =0;
                for(auto const way_point : waypoints){
                    // std::cout<< count << std::endl;
                    _curve->add_way_point(Vector(way_point[0], way_point[1], way_point[2]));
                    // count++;
                }
                // std::cout<<"=====================34========================"<< std::endl;

                _curve->add_way_point(Vector(waypoints.back()[0], waypoints.back()[1], waypoints.back()[2]));
                
                std::cout << "Nodes: " << _curve->node_count() << std::endl;
	            std::cout << "Total length: " << _curve->total_length() << std::endl;
            }

                
            std::vector<Eigen::VectorXf> TrajectorySmoother::get_smoothed_trajectory(){
                std::vector<Eigen::VectorXf> new_path;
                for (int i = 0; i < _curve->node_count(); ++i) {
                    Eigen::VectorXf pose(4);
                    auto node = _curve->node(i);
                    pose<< node.x, node.y, node.z, 1.0; 
                    new_path.push_back(pose);
	            }
                return new_path;
            }

            // https://math.stackexchange.com/questions/1905533/find-perpendicular-distance-from-point-to-line-in-3d
            float TrajectorySmoother::get_distance(Eigen::VectorXf pont_a, Eigen::VectorXf pont_b, Eigen::VectorXf pont_c){
                Eigen::VectorXf d = (pont_c - pont_a);
                if(d.norm() != 0){
                    d = (pont_c - pont_a)/(pont_c - pont_a).norm();
                }
                Eigen::VectorXf v = (pont_b - pont_a);
                float t = v.dot(d);
                Eigen::VectorXf p = pont_a + t*d;
                float dis = (p-pont_b).norm();
                return dis;
            } 
    }
}
