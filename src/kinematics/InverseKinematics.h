#pragma once
#include "ofMain.h"
#include "RobotModel.h"
#include "Pose.h"
#include "RobotConstants.hpp"
#include "RelaxedIKSolver.h"
//
// Copyright (c) 2016, 2021 Daniel Moore, Madeline Gannon, and The Frank-Ratchye STUDIO for Creative Inquiry All rights reserved.
//

// These kinematics find the tranfrom from the base link to the end effector.
// Though the raw D-H parameters specify a transform from the 0th link to the 6th link,
// offset transforms are specified in this formulation.
// To work with the raw D-H kinematics, use the inverses of the transforms below.

// Transform from base link to 0th link
// -1,  0,  0,  0
//  0, -1,  0,  0
//  0,  0,  1,  0
//  0,  0,  0,  1

// Transform from 6th link to end effector
//  0, -1,  0,  0
//  0,  0, -1,  0
//  1,  0,  0,  0
//  0,  0,  0,  1

namespace ofxRobotArm
{

    class InverseKinematics
    {
    public:
        ~InverseKinematics();
        InverseKinematics();
        void setup(ofxRobotArm::RobotType robotType, ofxRobotArm::IKType ikType, vector<double> pose, RobotModel * model);
        void setSWParams(float _a1, float _a2, float _b, float _c1, float _c2, float _c3, float _c4);
        void setDHParams(float d1, float a2, float a3, float d4, float d5, float d6);
        void setRobotType(ofxRobotArm::RobotType type);
        void setIKType(ofxRobotArm::IKType type);
        //int selectSolution(vector<vector<double> > & inversePosition, vector<double> currentQ, vector<double> weight);
        ofMatrix4x4 forwardKinematics(vector<double> pose);
        vector<vector<double>> inverseKinematics(ofxRobotArm::Pose targetPose, ofxRobotArm::Pose currentPose);
        void forward(double *q, double *T);
        void setRelaxedPose(vector<double> pose);
        vector<double> inverseRelaxed(Pose targetPose, Pose currentPose);
        vector<vector<double>> inverseHK(ofxRobotArm::Pose targetPose);
        vector<vector<double>> inverseSW(ofxRobotArm::Pose targetPose);
        //adapted from https://github.com/Jmeyer1292/opw_kinematics/blob/master/include/opw_kinematics/opw_kinematics_impl.h
        // based upon An Analytical Solution of the Inverse Kinematics Problem of Industrial Serial Manipulators with an Ortho-parallel Basis and a Spherical Wrist
        ofMatrix4x4 forwardSW(double t1, double t2, double t3, double t4, double t5, double t6);
        int inverseSW(ofMatrix4x4 pose, double *sol);
        ofMatrix4x4 forwardHK(double o, double t, double th, double f, double fi, double s);
        void forwardHK(double *q, double *T);
        void forward_allHK(double *q, double *T1, double *T2, double *T3, double *T4, double *T5, double *T6);
        int inverseHK(double *T, double *q_sols, double q6_des = 0.0);
        void computeDH(RobotModel * model);
        void harmonizeTowardZero(vector<double>& qs);
        bool isValid(vector<double>& qs);
        void inverse(ofMatrix4x4 *target, vector<vector<double>> &sol);

        vector<double> boundSolution(vector<double> thetas);
        double * toIK(ofMatrix4x4 input);
        ofMatrix4x4 toOF(double *T);

        vector<double> initPose;
        ofxRobotArm::RobotType robotType;
        ofxRobotArm::IKType ikType;
        ofParameterGroup params;

        vector<vector<double>> preSol;

        RelaxedIKSolver relaxedIK;
        // Retrive a specific value from a 4x4 matrix
        float get(ofMatrix4x4 mat, int row, int col);

        double d1;
        double a2;
        double a3;
        double d4;
        double d5;
        double d6;

        double a1, a2_2, b, c1, c2, c3, c4;
        vector<double> offsets;
        vector<double> sign_corrections;
        vector<double> joint_limit_min;
        vector<double> joint_limit_max;
        vector<vector<double>> preInversePosition;
    };
}
