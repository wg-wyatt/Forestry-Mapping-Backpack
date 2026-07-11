# Forestry-Mapping-Backpack

<!-- Insert Cover Image Here -->

---

## Overview
The LiDAR Backpack Mapping System is a modular mobile sensing platform designed for ecological and forestry data collection. The system integrates a rotating LiDAR sensor, inertial measurement unit (IMU), onboard processing, and custom electronics into a compact, field-deployable package capable of generating high-resolution three-dimensional point clouds. This project encompassed the complete mechanical and electrical design process, including CAD modeling, sheet metal design, custom PCB development, system architecture, MATLAB-based engineering analysis, and structural simulation. The design emphasizes manufacturability, modularity, and ease of assembly while remaining suitable for low-volume fabrication.

## Project Disclaimer

This project was completed in collaboration with the Purdue Forestry Department. Certain project details, files, and implementation documentation may be limited due to sponsor requirements and intellectual property considerations.

---

## Key Features

- Rotating LiDAR platform
- Integrated IMU for spatial orientation
- Modular mechanical architecture
- MATLAB analysis supporting point cloud generation
- Timing belt-driven rotation system
- Custom KiCad PCB
- FEA-validated structural design
- Optimized for low-volume manufacturing

---

## Problem Statement

The Purdue Forestry Department developed a machine learning–based plant recognition system to assist researchers with ecological surveying and vegetation analysis. To improve the usability of the sensing platform during field deployment, the department sought a redesigned LiDAR mounting system that would better support extended hiking through uneven terrain while maintaining high-quality data collection.

The existing system mounted a fixed LiDAR sensor on a tall support mast attached to a backpack frame. While functional, this configuration positioned a significant portion of the system mass away from the user's center of gravity, reducing comfort and stability during long hikes. Additionally, the fixed sensor orientation limited the flexibility of data acquisition and constrained future scanning strategies.

The objective of this project was to design a manufacturable LiDAR mounting system that relocated the sensor closer to the user's center of mass, incorporated a secondary axis of rotation to expand scanning capability, and integrated the required mechanical, electrical, and software subsystems into a compact field-deployable package. The design was intended for low-volume fabrication using conventional manufacturing processes while supporting future prototype construction and validation.

---

## Design Requirements

The following design requirements were established during the concept development phase to guide system architecture and engineering decisions. Requirements were selected to balance field usability, sensing performance, manufacturability, and compatibility with the existing Purdue Forestry Department backpack platform.

### Mechanical Requirements

| ID | Requirement | Target | Verification Method |
|----|-------------|--------|---------------------|
| DR-01 | Total system weight | < 5 kg (excluding backpack) | CAD mass properties |
| DR-02 | Structural durability | Withstand 5 g loading without structural failure | Finite Element Analysis (FEA) |
| DR-03 | Manufacturability | Components shall be manufacturable using conventional CNC machining, sheet metal fabrication, additive manufacturing, and commercially available hardware | Design review and manufacturing drawings |
| DR-04 | Serviceability | Electronics and wearable components shall be removable without permanent modification to the assembly | Assembly review |

### Functional Requirements

| ID | Requirement | Target | Verification Method |
|----|-------------|--------|---------------------|
| FR-01 | Point cloud coverage | Provide 360° scanning with a secondary axis of rotation to improve spatial coverage and reduce occlusions | MATLAB analysis and future field validation |
| FR-02 | Rotational position tracking | Report motor position to ±0.01° for point cloud reconstruction | Encoder specification and software verification |

### Integration Requirements

| ID | Requirement | Target | Verification Method |
|----|-------------|--------|---------------------|
| IR-01 | Backpack compatibility | Integrate with the existing Purdue Forestry backpack frame, 24 V hot-swappable M18 battery system, and existing data interfaces | CAD integration and electrical design review |
| IR-02 | Environmental protection | Minimum enclosure protection equivalent to IP32 | Enclosure design review and future ingress testing |

---

## System Architecture

The LiDAR Backpack Mapping System was designed as a modular mechatronic platform integrating sensing, motion control, power management, and onboard computation. The system architecture was developed to allow independent development and maintenance of each subsystem while maintaining compatibility with the existing Purdue Forestry Department backpack platform.

The system is composed of four primary subsystems:

1. **Sensing System** — LiDAR and IMU sensors responsible for collecting spatial and orientation data.
2. **Motion Control System** — Motor, encoder, and controller responsible for rotating the LiDAR sensor and providing rotational position feedback.
3. **Power Distribution System** — Battery, voltage regulation, and protection circuitry responsible for supplying power to all electrical components.
4. **Processing and Data System** — Embedded computing platform responsible for sensor communication, data synchronization, and point cloud generation.

<!-- Insert System Architecture Diagram Here -->

### Sensing System

The sensing subsystem consists of an Ouster OS1 LiDAR sensor paired with an Ellipse N inertial measurement unit (IMU). The LiDAR provides high-resolution three-dimensional measurements, while the IMU provides time synchronization and orientation information required for accurate spatial reconstruction. Combining LiDAR measurements with rotational position feedback enables the generation of a complete point cloud from the scanning platform.

### Motion Control System

The motion control subsystem provides controlled rotation of the LiDAR assembly through a motor-driven mechanism. A geared timing belt transmission was selected to ensure stable torque transmission during operation. Encoder feedback is used to track rotational position and synchronize the scanning motion with collected sensor data.

### Power Distribution System

The system operates using a 24 V hot-swappable battery architecture inherited from the existing backpack platform. Power is distributed to the LiDAR, motor controller, embedded electronics, and onboard computer through dedicated power regulation and distribution hardware.

<!-- Insert Power Architecture Diagram Here -->

### Processing and Data System

The processing subsystem uses an NVIDIA Jetson Orin platform to collect sensor data, synchronize measurements, and generate three-dimensional point clouds. Communication between the LiDAR, IMU, motor controller, and processing hardware was designed to maintain reliable data transfer while minimizing external wiring.

### System Integration

The final architecture integrates mechanical, electrical, and software subsystems into a modular platform designed for field deployment. Interfaces were intentionally designed to support assembly, maintenance, and future improvements without requiring complete system redesign.

---

## Mechanical Design


---

## Electrical Design


---

## Software Architecture


---

## Engineering Analysis

Engineering analysis was used to establish design parameters and validate critical system decisions. The analysis process began by evaluating the relationship between LiDAR measurement characteristics and scanning motion, which informed the required rotational velocity of the system. Mechanical drive calculations were then performed to select an appropriate transmission design, followed by structural analysis of the final assembly.

### MATLAB Scanning Analysis

To ensure complete point cloud coverage, a MATLAB model was developed to evaluate the relationship between the LiDAR's internal measurement frequency and the rotational speed of the secondary scanning axis.

The LiDAR sensor collects spatial measurements at a fixed internal dispersion frequency. Because the sensor was mounted on a rotating platform, the angular displacement between consecutive measurements depended on the rotational velocity of the secondary axis. An incorrect rotational speed could result in insufficient point density, uneven coverage, or gaps within the generated point cloud.

The MATLAB model incorporated the LiDAR measurement frequency and simulated the effect of varying secondary axis rotational speeds on point cloud coverage. Multiple rotational velocities were evaluated to determine the operating range that provided continuous spatial coverage while maintaining practical mechanical constraints.

The resulting analysis established the required rotational velocity of the LiDAR assembly, which was then used as a design input for the motor and timing belt transmission calculations. Add the details(final rpm, lidar rpm, lidar spec)

<!-- Insert MATLAB plot/simulation image here -->

<!-- Insert MATLAB plot/simulation code here -->

### Rotation System and Gear Design

The rotational axis was designed to provide controlled motion of the LiDAR assembly while satisfying the rotational velocity requirements established through MATLAB scanning analysis. The drivetrain design focused on selecting a reliable transmission method that could provide the required speed reduction, torque capacity, and compact packaging.

A T2 timing belt system was selected due to its suitability for compact motion transmission and availability of standardized pulley components. Based on manufacturer recommendations, the design targeted a 5:1 reduction ratio to balance torque multiplication, rotational speed, and reliable belt engagement.

The drivetrain geometry was developed from the selected motor pulley. The driven pulley size was calculated based on the required reduction ratio, and the resulting center-to-center spacing and belt length were determined to ensure proper belt fit and operation.

Key calculations included:

- Driven pulley sizing based on required gear ratio
- Pulley center separation distance
- Required timing belt length
- Rotational velocity after reduction
- Torque required to rotate the LiDAR assembly
- Motor startup torque under load conditions

The final transmission design provided the required rotational speed while maintaining sufficient torque capacity to rotate the LiDAR assembly and associated mechanical components.

<!-- Insert timing belt sketch/calculations here -->

<!-- Insert drivetrain CAD image here -->

### Structural Analysis (FEA)


---

## Design for Manufacturing

The LiDAR Backpack Mapping System was designed with low-volume fabrication in mind. While the system was developed as a research prototype, the mechanical architecture prioritized manufacturability, accessibility of components, and ease of assembly using processes available to small-scale fabrication shops.

### Manufacturing Approach

The design utilizes a combination of conventional manufacturing methods including CNC machining, sheet metal fabrication, additive manufacturing, and commercially available hardware. Manufacturing processes were selected based on part function, required precision, and cost considerations.

Critical structural and alignment features were designed around machinable interfaces, while non-critical components were designed to reduce manufacturing complexity and allow rapid iteration.

### Component Selection

Commercially available components were incorporated where possible to reduce custom fabrication requirements. Examples include:

- Timing belt and pulley components
- Bearings
- Fasteners
- Motor and encoder hardware
- Electrical connectors

Using standardized components reduces lead times, simplifies replacement, and improves long-term serviceability.

### Assembly and Serviceability

The system was designed as a modular assembly with separate mechanical, electrical, and sensing components. This approach allows individual subsystems to be accessed, replaced, or modified without requiring complete disassembly of the platform.

Design considerations included:

- Accessible fasteners
- Modular enclosure design
- Cable routing considerations
- Separation of structural and electronic components

### Future Manufacturing Considerations

If transitioned from prototype design to production, additional engineering documentation would be developed, including detailed manufacturing drawings, tolerance specifications, and GD&T on critical interfaces.

Potential future manufacturing validation would include:

- Fabrication of prototype components
- Assembly verification
- Dimensional inspection
- Structural testing


---

## Project Status

## Project Status

The LiDAR Backpack Mapping System was developed as part of a senior design project in collaboration with the Purdue Forestry Department. The project progressed through multiple design iterations, beginning with the development of a benchmark system and continuing toward a fully integrated field-deployable platform.

### Benchmark System

An initial benchmark system was developed by the senior design team to provide a functional platform for evaluating the plant recognition workflow. This system utilized lower-grade electronics and a simplified mounting approach that allowed it to be installed on the existing backpack platform.

The benchmark system established a baseline hardware configuration and provided a foundation for future development. Further validation of the benchmark system with the plant recognition algorithm is planned.

### Integrated System Design

The current iteration focuses on integrating the complete sensing, motion, power, and processing architecture into a single manufacturable platform. The detailed design phase has been completed, including:

- Mechanical system design
- Sensor and hardware integration
- Electrical architecture development
- Motion system analysis
- MATLAB-based scanning analysis
- Manufacturing considerations

The system is currently at the fabrication-ready stage. Fabrication and physical validation will proceed upon sponsor approval and project continuation.

---

## Future Work


---

## Skills Demonstrated


