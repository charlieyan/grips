#pragma once

#include <utility>

// Base class for all the steering functions
class GNode_base
{
public:

    virtual ~GNode_base() = default;

    /// Cost associated to the best Node selected
    float steer_cost;

    /// Flag for optimization of the orientations
    int OPTM_ORIENTATIONS;

    /// Number of outgoing edges per node
    int nEdges;

    /// Cost per each orientation associated to the node
    double *costs;

    /// array of possible orientations
    double *orientations;


    /// flag to read orientations from Map
    int READ_OR;

    int CHECK_SUCCESSOR;

    int goal_x;
    int goal_y;

    int start_x;
    int start_y;

    /// X and Y coordinates of the Node
    int x, y;

    double x_r, y_r;

    /// Flag to indicate if node hase been generated by a steering function
    bool steer;

    /// Orientation associated to the best node
    double theta;

    /// Occupied to true if the node is on a obstacle cell
    bool occupied;

    bool hasParent;

    GNode_base *parent;
    GNode_base *child;

    // ============================================================================================
    /// line(GNode *successor,GNode *parent_node)
    /// Check if there is a geometric line of sight between the two nodes
    /// ============================================================================================
    static bool line(const GNode_base *successor, const GNode_base *parent_node);

    static bool line(double x0, double y0, double y1, double x1);

    // ============================================================================================
    /// bool isblock(double x, double y)
    /// Check if the cell is blocked by an obstacle
    /// ============================================================================================
    static bool isblock(double x, double y);
};

struct GNodeComparator
{
    bool operator()(GNode_base const &lhs, GNode_base const &rhs) const
    {
        static const double tolerance = 1e-14;

        if (lhs.x_r + tolerance < rhs.x_r)
            return true;
        if (lhs.x_r + tolerance > rhs.x_r)
            return false;

        if (lhs.y_r + tolerance < rhs.y_r)
            return true;
        if (lhs.y_r + tolerance > rhs.y_r)
            return false;

        if (lhs.theta + tolerance < rhs.theta)
            return true;
        if (lhs.theta + tolerance > rhs.theta)
            return false;

        return false;
    }

    bool operator()(std::pair<GNode_base, GNode_base> const &lhs,
                    std::pair<GNode_base, GNode_base> const &rhs) const
    {
//        return ((*this)(lhs.first, rhs.first)
//                || (!(*this)( lhs.first, rhs.first)
//                &&  !(*this)( rhs.first, lhs.first)
//                &&   (*this)(lhs.second, rhs.second)));
        static const double tolerance = 1e-14;

        if (lhs.first.x_r + tolerance < rhs.first.x_r)
            return true;
        if (lhs.first.x_r + tolerance > rhs.first.x_r)
            return false;

        if (lhs.first.y_r + tolerance < rhs.first.y_r)
            return true;
        if (lhs.first.y_r + tolerance > rhs.first.y_r)
            return false;

        if (lhs.first.theta + tolerance < rhs.first.theta)
            return true;
        if (lhs.first.theta + tolerance > rhs.first.theta)
            return false;

        if (lhs.second.x_r + tolerance < rhs.second.x_r)
            return true;
        if (lhs.second.x_r + tolerance > rhs.second.x_r)
            return false;

        if (lhs.second.y_r + tolerance < rhs.second.y_r)
            return true;
        if (lhs.second.y_r + tolerance > rhs.second.y_r)
            return false;

        if (lhs.second.theta + tolerance < rhs.second.theta)
            return true;
        if (lhs.second.theta + tolerance > rhs.second.theta)
            return false;

        return false;
    }
};
