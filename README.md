# ProgettoBasi: Basi di Dati per la Gestione di un Sistema di Spedizioni 📦
A comprehensive database system for managing shipping operations, developed as a university project for the Database course at the Department of Mathematics, University of Padova.

## 👥 Authors
- **Lorenzo Soligo** - 2101057
- **Pietro Bassi** - 2137999

## 📋 Project Overview

This project develops a structured and coherent database system for managing information related to packages, customers, couriers, and shipping company branches. The main objective is to provide a system that monitors package transport through all delivery steps while managing related data and ensuring organized access for analysis.

## 🎯 Key Features

### Package Types
The database distinguishes between three types of packages:

- **Bundle Packages** 📦: Aggregator packages for a single order
- **Insured Packages** 🛡️: Packages with different types of insurance coverage
- **Gift Packages** 🎁: Packages with dedications and special wrapping

### Tracking System
A comprehensive tracking system that links package IDs with timestamps to build a historical record of status and position updates for each package.

## 📊 Database Schema

### Main Entities

- **Pacco (Package)**: Core package information with unique alphanumeric ID
- **Cliente (Customer)**: Customer information identified by email
- **Corriere (Courier)**: Courier information with CF identification
- **Filiale (Branch)**: Company branches (Lockers, Control Points, Warehouses)
- **Tracking**: Historical tracking data for packages

### Package Specializations

#### Bundle Packages
- Quantity of packages in a bundle
- Recursive structure for package aggregation

#### Insured Packages
Insurance types:
- 30-day return policy
- 1-year warranty
- 3-year warranty

#### Gift Packages
Wrapping options:
- Gift paper
- Canvas bag
- Special box
- Optional dedication

### Tracking Status
- Delivered
- In Delivery
- Shipped
- Authorized
- Control Phase

## 🏗️ Database Design

### Conceptual Design
The system uses an Entity-Relationship model with careful attention to:
- Recursive structure for Bundle packages
- Historical tracking through timestamp-based records
- Courier seat assignments with current/past status

### Logical Design
- **Redundancy Analysis**: Maintained `PACCHIATTIVI` attribute in `CORRIERE` for optimization
- **Generalization Elimination**: Hybrid approach for package specializations
- **Relational Schema**: Complete normalization with foreign key constraints

## 🔍 Query Examples

The system includes 5 optimized queries:

1. **Average cost** of packages from couriers of a certain grade passing through specific branch types
2. **Bundle package count** with 3-year warranty
3. **Couriers** with above-average delivery times
4. **Couriers** with insured/gift bundles above specific cost thresholds
5. **Latest tracking update** for packages

## 🚀 Implementation

### Database Management System
- **PostgreSQL** with Supabase hosting
- Optimized indexing strategy for query performance
- Parameterized queries to prevent SQL injection

### Application Interface
- C application (`code.c`) for database interaction
- User-friendly query execution interface
- Enum-based parameter validation for security

## 📈 Performance Optimization

### Index Strategy
- Hash indexes for JOIN conditions
- B+Tree indexes for GROUP BY operations
- Composite indexes for multi-column conditions

### Redundancy Analysis
Cost analysis showed maintaining the `PACCHIATTIVI` redundant attribute reduces total operation cost from 12,288 to 1,128 daily accesses.

## 🛠️ Technical Requirements

- PostgreSQL database
- C compiler for application interface
- Supabase account for cloud database hosting

## 📋 Database Tables

### Core Tables
- `Pacco`: Package information with customer and courier references
- `Cliente`: Customer profiles with contact information
- `Corriere`: Courier data with availability and activity tracking
- `Filiale`: Branch locations and types
- `Tracking`: Time-stamped package status history
- `Bundle-Pacchi`: Bundle composition with quantities
- `Sede`: Courier-branch assignment history

## 🔧 Setup Instructions

1. **Database Setup**
   ```sql
   -- Execute the provided SQL schema
   -- Import sample data
   -- Create indexes for optimization
   ```

2. **Application Compilation**
   ```bash
   gcc -o shipping_app code.c -lpq
   ```

3. **Configuration**
   - Set up Supabase connection parameters
   - Configure database credentials
   - Test connection and queries

## 📝 Usage

The application provides an interactive menu for:
- Executing predefined queries with parameters
- Viewing package tracking information
- Analyzing courier performance
- Managing bundle compositions

## 🎓 Academic Context

This project was developed for the Database course (Basi di Dati) as part of the Bachelor's degree in Computer Science at the University of Padova, Department of Mathematics.

## 📄 Documentation

The complete project documentation includes:
- Requirement analysis
- Conceptual design with ER diagrams
- Logical design and schema optimization
- Implementation details and query definitions
- Performance analysis and indexing strategy

## 🔍 Future Enhancements

- Trigger implementation for automatic attribute updates
- Enhanced constraint checking across multiple tables
- Real-time tracking interface
- Mobile application integration

---

*This project demonstrates practical application of database design principles, from conceptual modeling to optimized implementation, focusing on real-world shipping management scenarios.*
