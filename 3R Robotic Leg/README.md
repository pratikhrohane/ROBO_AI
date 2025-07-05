### ✅ **3R Robotic Leg**

**Design a leg for the Spot robot using a 3R planar mechanism.**

You are expected to:

1. **Model the leg as a 3R planar mechanism**, meaning:

   * It has **3 revolute (rotating) joints**.
   * It operates in a **2D plane** (usually XZ plane).
   * It mimics the basic structure of robotic legs like Spot or HADE.

2. **Implement one or more of the following:**

   * **Kinematics**: Forward and/or Inverse Kinematics calculations for the leg.
   * **Transmission**: Mechanical or motor-based system to drive the joints.
   * **Structural Design**: CAD modeling of the leg in a tool like Fusion 360.

> ✅ **You can do just one or multiple of the above — more than one is appreciated.**

---


## 🧠 Concept Inspiration

While researching **3R planar leg mechanisms**, I came across the design of **Redundant Articulated Legs** used in advanced quadruped robots. A standout example is the **HADE (Hybrid Actuator Development) Leg**, which simulates the biomechanics of a horse's leg.

<img src="images/Redundant_Articulated_Legs.jpeg" alt="Redundant Articulated Legs" width="500"/>
<img src="images/HADE.jpeg" alt="HADE Hybrid Actuator Development" width="500"/>

The HADE-inspired structure consists of:

* **Three segments**: Thigh, Shank, and Foot
* **Three joints**: Hip, Knee, and Ankle

This configuration forms a **3R planar chain** capable of high degrees of motion and control within a vertical plane (XZ). It's particularly effective for achieving a **high payload-to-weight ratio**, which is critical in agile quadrupeds.


---


## 🛠️ Structural Design — 3R Planar Leg

Inspired by the **HADE leg mechanism**, I designed a **3R planar robotic leg** using Fusion 360. The structure mimics a horse-like leg consisting of:

* **Thigh**
* **Shank**
* **Foot**

Each segment is connected through:

* **Hip Joint (R1)**
* **Knee Joint (R2)**
* **Ankle Joint (R3)**

The leg is modeled to move in a **2D vertical plane (XZ)**, forming a **3R serial chain** — ideal for simulating walking or climbing motions in quadruped robots like Spot or HADE.

---

### 📐 Leg Dimensions (Based on Fusion 360 Model)

| Segment | Label | Length (mm) |
| ------- | ----- | ----------- |
| Thigh   | L1    | 453.018     |
| Shank   | L2    | 453.056     |
| Foot    | L3    | 188.056     |

---

### 🧰 CAD Design Output

Below is the 3-view representation of the leg structure modeled in Fusion 360:

<p align="center">
  <img src="images/3R_Planner_Leg.png" width="300"/>
  <img src="images/3R_Planner_Leg_Front_View.png" width="300"/>
  <img src="images/3R_Planner_Leg_Back_View.png" width="300"/>
</p>

*Figure: Isometric, Front, and Back views of the 3R Planar Robotic Leg*

---

### 🔗 Download Fusion 360 Model

You can download the complete `.f3d` model using the link below:

> [📁 3R\_Planner\_Leg.f3d](models/3R_Planner_Leg.f3d)

---


Thanks! Here's a complete and well-structured **Transmission System** section, now fully referencing the **HADE prototype** details you provided.

This version includes:

* Accurate use of SEAs at hip and knee
* Passive spring at ankle with stiffness value
* Details on encoders and control
* A 2-image layout (`HADE Ele.png`, `3R Planner Leg.gif`)

---

## ⚙️ Transmission System

To physically simulate and actuate the 3R planar robotic leg, we explored a transmission approach inspired by the **HADE leg prototype**, which is an under-actuated, horse-leg-inspired mechanism.

---

### 🦿 Reference: HADE Leg Prototype (Hybrid Actuator Development)

<p align="center">
  <img src="images/HADE_Ele.jpeg" width="400"/>
  <img src="images/3R_Planner_Leg.gif" width="400"/>
</p>

> *Figure: HADE leg electrical diagram (left) and our 3R planar leg animation (right)*

The HADE prototype serves as a direct inspiration for our transmission layout and control design.

---

### 🔩 Transmission Configuration (HADE-Inspired)

| Joint     | Type                    | Transmission Method                                 |
| --------- | ----------------------- | --------------------------------------------------- |
| **Hip**   | Active                  | Series Elastic Actuator (SEA) + Encoder             |
| **Knee**  | Active                  | Series Elastic Actuator (SEA) + Encoder             |
| **Ankle** | Passive (Underactuated) | Extension spring (`Kₛ = 3113 N/m`) + Linear encoder |

---

### 🧠 Detailed Features from HADE:

* **Series Elastic Actuators (SEA)** at Hip and Knee

  * Include **spring + encoder** to sense joint force (1.2 N per count)
  * Position encoder with a resolution of **50.8 μm per count**
  * Provide **compliance + force feedback** in actuation
* **Ankle Joint**

  * **Not motorized**: actuated by an **extension spring**
  * Linear encoder resolution: **224 μm per count**
  * Torque sensing resolution: **0.69 N per count**
* **Control & Sensing**

  * PID controllers for Hip and Knee based on **inverse kinematics**
  * Spring deflection used to estimate **joint torque**
  * Ground contact detected through **ankle spring torque**

---

### 💡 What This Teaches Us

* **SEAs enable compliant motion**, useful for real-world ground interaction
* **Underactuation reduces energy needs**, especially for ankle joints
* **Force sensing via spring deflection** provides safe torque control
* **Encoder-based feedback** ensures accurate closed-loop control
* **Vertical-only motion constraint** simplifies analysis and testing

---

**Kinematics of a 3R Planar Robotic Leg**



## 1. System Overview

The robotic leg modeled in Fusion 360 consists of three rigid links and three revolute joints (3R), forming a planar manipulator that operates in the XZ plane. It resembles the leg structure of quadrupedal robots like Boston Dynamics' Spot or the SEA-driven HADE leg.

### Link Lengths (as per Fusion 360 model):

* Thigh (L1): 453.018 mm
* Shin  (L2): 453.056 mm
* Foot  (L3): 188.056 mm

All joints rotate in the plane, and we assume counterclockwise rotation is positive.

---

## 2. Forward Kinematics

### 🎯 Goal:

To find the foot position `(x, z)` based on the current angles of the hip, knee, and ankle motors.

### 📥 Inputs:

* `theta1`: Hip joint angle (in degrees or radians)
* `theta2`: Knee joint angle (relative to thigh)
* `theta3`: Ankle joint angle (relative to shin)

### 🧠 Logic:

The robot leg has 3 links connected in series.

1. First link (thigh) rotates by `theta1`
2. Second link (shin) rotates by `theta2` **relative to the thigh**
3. Third link (foot) rotates by `theta3` **relative to the shin**

### 🪜 Steps:

1. Add up the angles cumulatively:

   * `a1 = theta1`
   * `a2 = theta1 + theta2`
   * `a3 = theta1 + theta2 + theta3`

2. For each link, calculate its `(x, z)` contribution:

   * Link 1: `(x1, z1)` = `(L1 * cos(a1), L1 * sin(a1))`
   * Link 2: `(x2, z2)` = `(L2 * cos(a2), L2 * sin(a2))`
   * Link 3: `(x3, z3)` = `(L3 * cos(a3), L3 * sin(a3))`

3. Total foot position:

   * `x = x1 + x2 + x3`
   * `z = z1 + z2 + z3`

### 📤 Output:

* `x`: Horizontal position of the foot
* `z`: Vertical position of the foot

You can implement this easily in Arduino using `cos()` and `sin()` functions after converting degrees to radians.

---

## 3. Inverse Kinematics

### 🎯 Goal:

To find the angles `theta1`, `theta2`, and `theta3` needed to move the foot to a given position `(x, z)` with a desired orientation `phi`.

### 📥 Inputs:

* `x, z`: Target position of the foot
* `phi`: Desired angle of the foot (i.e., end angle of total leg)

### 🪜 Steps:

1. Subtract the foot link’s contribution:

   * `x' = x - L3 * cos(phi)`
   * `z' = z - L3 * sin(phi)`

2. Now solve the triangle between hip, knee, and ankle base (L1, L2):

   * Find distance `r` = sqrt(`x'^2 + z'^2`)
   * Use Law of Cosines to find `theta2`

     * `cos(theta2) = (r² - L1² - L2²) / (2 * L1 * L2)`
     * `theta2 = acos(...)`

3. Find `theta1` using two vectors:

   * First vector: angle to `(x', z')` using `atan2(z', x')`
   * Second vector: triangle internal angle using `atan2(...)`
   * `theta1 = atan2(z', x') - atan2(...)`

4. Compute `theta3`:

   * `theta3 = phi - (theta1 + theta2)`

### 📤 Output:

* `theta1`, `theta2`, `theta3`: Angles to set each joint to reach foot target

### ⚠️ Notes:

* IK may return 2 solutions: elbow-up and elbow-down
* Use bounds or physical constraints to choose the valid one
* Make sure `acos()` input is in range \[-1, 1] to avoid math error

This method is clean and can be implemented directly in Arduino using trigonometric functions.

---

## 4. Use in Arduino

* Use `sin()` and `cos()` functions for FK
* Use `sqrt()`, `atan2()`, and `acos()` for IK
* Convert degrees ↔ radians as needed: `radians = degrees * PI / 180`
* PID or servo commands can use these angles directly

---

