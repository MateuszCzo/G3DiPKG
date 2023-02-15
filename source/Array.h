#ifndef ARRAY_CLASS_H
#define ARRAY_CLASS_H


/// <summary>
/// The Field structure represents 1 field on the board
/// </summary>
/// if there is a ship and if the field has been shot
struct Field
{
	bool isShot;
	bool isShip;
};

/// <summary>
/// stores information about a player's board
/// </summary>
class Array
{
private:
	Field** array;

public:
	/// <summary>
	/// constructor
	/// </summary>
	/// initializes arrays
	Array();

	/// <summary>
	/// Shoots at the given place
	/// </summary>
	/// <param name="x">column number</param>
	/// <param name="y">row number</param>
	/// <returns>true if ship has been hit</returns>
	bool shoot(int x, int y);

	/// <summary>
	/// Retrieving field data from the given place
	/// </summary>
	/// <param name="x">column number</param>
	/// <param name="y">row number</param>
	/// <returns>Field structure that contains information whether there is a ship and whether the field has been shot</returns>
	const Field getFieldInfo(int x, int y);

	/// <summary>
	/// Putting the ship on the board
	/// </summary>
	/// <param name="x">column number</param>
	/// <param name="y">row number</param>
	/// <param name="orientation">orientation of the ship</param>
	/// <param name="length">ship length</param>
	/// orientation must be from 0 to 3
	/// <returns>true if the ship has been placed</returns>
	bool setShip(int x, int y, int orientation, int length);

	/// <summary>
	/// Checking if the player has lost
	/// </summary>
	/// <returns>true if the player has lost</returns>
	bool ifLose();

	/// <summary>
	/// Resets the player board
	/// </summary>
	void reset();
};

#endif // !ARRAY_CLASS_H