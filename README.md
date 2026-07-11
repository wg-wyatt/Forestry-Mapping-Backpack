# Forestry-Mapping-Backpack


---

## Overview
The LiDAR Backpack Mapping System is a modular mobile sensing platform designed for ecological and forestry data collection. 
The system integrates a rotating LiDAR sensor, inertial measurement unit (IMU), onboard processing, and custom electronics into a compact, field-deployable package capable of generating high-resolution three-dimensional point clouds.
This project encompassed the complete mechanical and electrical design process, including CAD modeling, sheet metal design, custom PCB development, system architecture, MATLAB-based engineering analysis, and structural simulation. 
The design emphasizes manufacturability, modularity, and ease of assembly while remaining suitable for low-volume fabrication.

---

## Key Features

- Rotating LiDAR platform
- Integrated IMU for telemetry
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


---

## Mechanical Design


---

## Electrical Design


---

## Software Architecture


---

## Engineering Analysis


---

## Design for Manufacturing


---

## Project Status


---

## Future Work


---

## Skills Demonstrated


