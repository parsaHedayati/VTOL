# VTOL Drone Simulation (ROS 2 + PX4)

This repository contains an **experimental VTOL drone simulation project** built using **ROS 2**, **Gazebo**, and **PX4 SITL**.  
The goal of the project is to explore **autopilot integration, system architecture, and simulation workflows** for VTOL UAVs.

> ⚠️ This project is **work in progress** and focuses on learning and system integration rather than a complete flight control implementation.

---

## Project Goals

- Integrate **PX4 SITL** with **ROS 2**
- Run a **VTOL vehicle** in a Gazebo simulation environment
- Understand **autopilot architecture**, flight modes, and ROS–PX4 communication
- Explore sensor topics, control interfaces, and simulation behavior
- Build a foundation for future work on navigation and control tuning

---

## Technologies Used

- **ROS 2**
- **PX4 Autopilot (SITL)**
- **Gazebo**
- **C / C++**
- **Python**
- **CMake / Make**

---

## Current Status

- PX4 SITL setup and basic integration
- ROS 2 ↔ PX4 communication exploration
- Gazebo-based VTOL simulation environment
- Initial testing of vehicle behavior and flight modes

Not yet implemented:
- Advanced control tuning
- Navigation and state estimation tuning
- Real flight data validation

## Project Structure
VTOL  /
├── src/ # Source code and integration logic\
├── scripts/ # Helper scripts\
├── CMakeLists.txt\
├── Makefile\
└── README.md\

---

## Notes

This project is intended for **educational and experimental purposes**.  
It serves as a hands-on introduction to **VTOL UAV systems**, **autopilot integration**, and **simulation-based testing**.

---

## Future Work

- Improve ROS 2 control interfaces
- Add basic navigation and state estimation experiments
- Refine VTOL transition behavior
- Validate simulation results against real flight data (if available)

---

## Author

**Parsa Hedayati**  
Electrical Engineering / Robotics  
📍 Riga, Latvia  

---

