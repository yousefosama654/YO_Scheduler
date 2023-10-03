<h1 class="center">YO_Scheduler</h1>
## Overview

YO_Scheduler is a straightforward OS scheduler designed to manage tasks based on time-triggered scheduling. It is specifically tailored for embedded systems and follows the classic platform AUTOSAR layered architecture. This README provides essential information about the project, its scheduling mechanism, the tasks it manages (namely `Led_Task()` and `Button_Task()`), and the hardware platform it is designed for.

## Table of Contents

- [Introduction](#introduction)
- [Scheduling Mechanism](#scheduling-mechanism)
- [Tasks](#tasks)
  - [Led_Task()](#led_task)
  - [Button_Task()](#button_task)
- [Hardware Platform](#hardware-platform)
- [AUTOSAR Layered Architecture](#autosar-layered-architecture)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [License](#license)

## Introduction

YO_Scheduler is a lightweight OS scheduler designed for time-triggered systems. It allows you to manage tasks based on specific time intervals, ensuring precise execution of tasks in embedded applications. The project includes two primary tasks, `Led_Task()` and `Button_Task()`, which are scheduled at different time intervals.

## Scheduling Mechanism

YO_Scheduler relies on a simple time-triggered scheduling mechanism. The scheduler runs periodically, and at each tick, it checks whether it's time to execute a task. The button task is scheduled to run every 20 ms, and the LED task every 40 ms. Button state transitions (pressed or released) are detected if a specific condition is met, where the button state remains stable for consecutive 60 ms.

## Tasks

### Led_Task()

`Led_Task()` is one of the tasks managed by YO_Scheduler. This task handles controlling an LED or a set of LEDs, allowing you to implement custom behavior or patterns based on the specified time interval.

### Button_Task()

`Button_Task()` is another task managed by YO_Scheduler. It is responsible for monitoring the state of a button. The button state is considered changed (pressed or released) when it remains stable for 60 ms, as per the project's requirements.

## Hardware Platform

YO_Scheduler is designed to run on the TM4C123GH6PM microcontroller, which is based on the Cortex-M4F core. The SysTick timer is used to handle the OS scheduling time, ensuring accurate and predictable task execution. Additionally, custom DIO (Digital Input/Output) and Port drivers have been implemented in accordance with AUTOSAR requirements to interact with the microcontroller's hardware peripherals.

## AUTOSAR Layered Architecture

YO_Scheduler adheres to the AUTOSAR layered architecture, a widely adopted framework for developing embedded systems. This architecture separates the software into different layers, ensuring modularity and scalability. YO_Scheduler can be integrated into an AUTOSAR-compliant system with ease.

## Getting Started

To get started with YO_Scheduler, follow these steps:

1. Clone the YO_Scheduler repository to your development environment.
2. Configure the scheduler parameters as needed (e.g., task intervals, hardware interface).
3. Build the project using your preferred toolchain, ensuring compatibility with the TM4C123GH6PM microcontroller.
4. Integrate YO_Scheduler into your AUTOSAR-based embedded system, taking advantage of the custom DIO and Port drivers.
5. Initialize and start the scheduler within your application code.

## Usage

Here's a simple example of how to use YO_Scheduler within your application code:

```c
#include "Os.h"

int main(void)
{
    /*
     * Start the Os to Init the Peripherals and Start Scheduling
     */
    Os_Start();
    return 0;
}
