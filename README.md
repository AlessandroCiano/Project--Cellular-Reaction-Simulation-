# Cellular Reaction Simulation

This project simulates the evolution of a system of chemical reactions within a cell, modeling how the presence or absence of specific substances affects reactions over discrete time steps. The program reads initial conditions and reaction rules, determines which reactions can occur at each step, and updates the cellular state accordingly.

## University of Milan-Bicocca
**Bachelor's Degree in Physics**  
**Academic Year**: 2021/2022  
**Course**: Computer Science Laboratory 1  
**Assignment Date**: June 2022  

## Problem Overview

In a living cell, reactions occur constantly, transforming reactants into products, potentially influenced by inhibitors. Each reaction is defined by:
- **Reactants**: substances required for the reaction.
- **Inhibitors**: substances that prevent the reaction.
- **Products**: substances produced by the reaction.

The initial state of the cell is defined by a set of substances present, and reactions are iteratively applied based on these rules.

## Input Specifications

1. **Initial Configuration**: The list of substances present in the cell at the start, given as integers.
2. **Reaction Rules**: Each rule includes:
   - An identifier (character)
   - Two reactants
   - One inhibitor
   - Two products

The input format requires each reaction on a separate line:
