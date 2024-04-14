//
//  main.cpp
//  N-Queens
//
//  Created by Lucas on 4/13/24.
//

#include <iostream>
#include <iomanip>
#include <vector>

// "Easier" and faster to keep in global
int attempts = 0;
int solutions = 0;

void PrintVector(const std::vector<int>& v)
{
    for (const int& i : v)
    {
        std::cout << std::setw(3) << i;
    }
    std::cout << std::endl;
}

// According to the way we use this function.
// only the "newest" queen can pose an issue
// with collisions with other queens
bool IsLegal(const std::vector<int>& v)
{
    // We are trying again!
    ++attempts;
    
    // Where is the "newest" queen on the board
    int value = v.back();
    
    // Test horizontally
    for (std::size_t i = 0; i < v.size() - 1; ++i)
    {
        if (v[i] == value)
        {
            return false;
        }
    }
    
    // Test diagonally
    int offset = 1;
    for (int i  = v.size() - 2; i >= 0; --i)
    {
        // Upwards
        if (value == v[i] + offset)
        {
            return false;
        }
        // Downwards
        if (value == v[i] - offset)
        {
            return false;
        }
        ++offset;
    }
    
    // There's no collision!
    return true;
}

// leftToPlace: The number of queens left to add to the board
// totalToPlace: The total number of queens that need to be added to the board
void NQueens(std::vector<int>& v, int leftToPlace, int totalToPlace)
{
    // This would mean we added all queens successfully!
    if (leftToPlace == 0)
    {
        ++solutions;
        PrintVector(v);
        return;
    }
    
    // Avoid so many pushes and pops by taking it out of the loop
    v.push_back(0);
    // Try to put a queen on all spaces [0, s)
    for (int i = 0; i < totalToPlace; ++i)
    {
        // Looks strange, but back() returns a reference!
        v.back() = i;
        // Only move on if the new queen doesn't collide with the others
        if (IsLegal(v))
        {
            NQueens(v, leftToPlace - 1, totalToPlace);
        }
    }
    v.pop_back();
}

void NQueens(int n)
{
    // Empty vector means board with no queens on it
    // Has to be passed in as a reference
    std::vector<int> v;
    v.reserve(n);
    // Call the "private" facing function
    NQueens(v, n, n);
}

int main()
{
    // Use the public facing function
    NQueens(8);
    
    // Output statistics
    std::cout << "Number of solutions: " << solutions << std::endl;
    std::cout << "Number of validity checks: " << attempts << std::endl;
    
    // End program
    return 0;
}
