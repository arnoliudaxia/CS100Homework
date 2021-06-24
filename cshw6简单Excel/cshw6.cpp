#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <stdlib.h>

// width of normal column and the row index column
const int DEFAULT_COLUMN_WIDTH = 7;
const int DEFAULT_ROW_IDX_WIDTH = 4;

// forward declaration of derived classes
class NumberSpreadSheetCell;
class StringSpreadSheetCell;

// types of spreadsheet cells
enum CellType { Number, String };

// The base SpreadSheetCell class 
class SpreadSheetCell
{
public:
	// constructors and destructors.
	SpreadSheetCell() {}
	~SpreadSheetCell() {}

	// output the content of cell
	friend std::ostream& operator<<(std::ostream& os, const SpreadSheetCell& cell)
	{
		if (cell.GetType() == CellType::Number)
		{
			//const NumberSpreadSheetCell& temp = static_cast<const NumberSpreadSheetCell&>(cell);
			os << std::setprecision(3) << cell.celldataN;
			return os;
		}
		else
		{
			os << (cell).celldataS;
			return os;
		}
	}

	// comparsion between two cells
	bool operator<(const SpreadSheetCell& that) const
	{

		if (this->GetType() == CellType::Number)
		{
			// return ((NumberSpreadSheetCell*)this)->celldataN < dynamic_cast<const NumberSpreadSheetCell&>(that).celldataN;
			/* const StringSpreadSheetCell* left = dynamic_cast<const StringSpreadSheetCell*>(this);
			 const StringSpreadSheetCell& right = dynamic_cast<const StringSpreadSheetCell&>(that);*/
			if (that.GetType() == CellType::String)return true;
			return this->celldataN < that.celldataN;
		}
		else
		{
			if (that.GetType() == CellType::Number)return false;

			return this->celldataS < that.celldataS;
		}

	}

	// get the type of this cell, returns either CellType::Number or CellType::String
	virtual CellType GetType() const = 0;
	double celldataN;
	std::string celldataS;
protected:
	CellType m_type; // stores the type of the cell (either CellType::Number or CellType::String)


};

class NumberSpreadSheetCell : public SpreadSheetCell
{

public:
	NumberSpreadSheetCell(double data)
	{
		celldataN = data;
	}
	CellType GetType() const {
		return CellType::Number;
	}


};

class StringSpreadSheetCell : public SpreadSheetCell
{
public:
	StringSpreadSheetCell(std::string data)
	{
		celldataS = data;
	}
	CellType GetType() const {
		return CellType::String;
	}
	virtual bool operator<(const SpreadSheetCell& that) const
	{
		return this->celldataS < dynamic_cast<const StringSpreadSheetCell&>(that).celldataS;
	}
};



class SpreadSheet
{
public:
	SpreadSheet(int rows, int cols);
	~SpreadSheet();

	// "hide" a row or column in this sheet, hidden row or column 
	// will not be shown in "ExportSheet" function
	void HideRow(int row);
	void HideColumn(int col);

	// re-show a hidden row or column in this sheet.
	// If the given row is not hidden, this does nothing.
	void ShowRow(int row);
	void ShowColumn(int col);

	void UpdateCell(int row, int col, SpreadSheetCell* cell);

	void ExportSheet(std::ostream& os);

	// PROBLEM 3: Sort all rows by the value in `col`, in accending order, and number < string < nullptr.
	void SortByColumn(int col);

private:
	std::vector<std::vector<SpreadSheetCell*>> m_cells;
	std::vector<int>visibilityMapRow;
	std::vector<int>visibilityMapCol;

	int rows, cols;
};

// PROBLEM 3: A functor class for sorting. It should have an operator() that takes 2 parameters.
class ColumnComparator
{
public:
	ColumnComparator(int col) :col(col) {}
	bool operator() (std::vector<SpreadSheetCell*> row1, std::vector<SpreadSheetCell*> row2) {
		auto col1 = row1[col - 1];
		auto col2 = row2[col - 1];
		if (!col2)return true;
		if (!col1)return false;
		if (col1->GetType() == CellType::Number && col2->GetType() == CellType::Number)
		{
			return col2->celldataN > col1->celldataN;
		}
		if (col1->GetType() == CellType::Number && col2->GetType() == CellType::String)
		{
			return true;
		}
		if (col1->GetType() == CellType::String && col2->GetType() == CellType::Number)
		{
			return false;
		}
		if (col1->GetType() == CellType::String && col2->GetType() == CellType::String)
		{
			return col2->celldataS > col1->celldataS;
		}


	}
	int col;
};

SpreadSheet::SpreadSheet(int rows, int cols) :rows(rows), cols(cols)
{
	for (size_t i = 0; i < rows; i++)
	{
		auto cells = new std::vector<SpreadSheetCell*>(cols, nullptr);
		m_cells.push_back(*cells);
		auto map = new std::vector<int>(cols, 1);
	}
	for (size_t i = 0; i < rows; i++)
	{
		visibilityMapRow.push_back(1);

	}for (size_t i = 0; i < cols; i++)
	{
		visibilityMapCol.push_back(1);

	}

}

SpreadSheet::~SpreadSheet()
{
	for (auto& col : m_cells)
		for (auto& e : col)
			delete(e);

}

void SpreadSheet::HideRow(int row)
{
	visibilityMapRow[row - 1] = 0;
}

void SpreadSheet::HideColumn(int col)
{
	visibilityMapCol[col - 1] = 0;

}

void SpreadSheet::ShowRow(int row)
{
	visibilityMapRow[row - 1] = 1;

}

void SpreadSheet::ShowColumn(int col)
{
	visibilityMapCol[col - 1] = 1;

}

void SpreadSheet::UpdateCell(int row, int col, SpreadSheetCell* cell)
{

	try
	{
		auto& element = m_cells.at(row - 1).at(col - 1);
		if (element != nullptr)delete(element);

		m_cells[row - 1][col - 1] = cell;
	}
	catch (const std::exception&)
	{

	}
}

void SpreadSheet::ExportSheet(std::ostream& os)
{
	int hiddencols = 0;
	using namespace std;
	//First Row
	os << setw(DEFAULT_ROW_IDX_WIDTH + 1) << "|";
	for (size_t i = 0; i < cols; i++)
	{
		if (visibilityMapCol[i])os << setw(DEFAULT_COLUMN_WIDTH) << i + 1;
		else hiddencols++;
	}
	os << endl;

	//Second Row
	for (size_t i = 0; i < DEFAULT_ROW_IDX_WIDTH + 1 + (cols - hiddencols) * DEFAULT_COLUMN_WIDTH; i++)
	{
		os << "-";
	}
	os << endl;
	//Data Row
	for (size_t i = 0; i < rows; i++)
	{
		if (visibilityMapRow[i] == 0)continue;
		os << setw(DEFAULT_ROW_IDX_WIDTH) << i + 1 << "|";
		for (size_t j = 0; j < cols; j++)
		{
			//
			if (visibilityMapRow[i] && visibilityMapCol[j])
			{
				if (m_cells[i][j])
					os << setw(DEFAULT_COLUMN_WIDTH) << *m_cells[i][j];
				else
					os << setw(DEFAULT_COLUMN_WIDTH) << " ";

			}
		}
		os << endl;

	}
}

void SpreadSheet::SortByColumn(int col)
{
	std::sort(m_cells.begin(), m_cells.end(), ColumnComparator(col));
	return;
	while (true)
	{
		bool flag = false;
		for (size_t i = 0; i < rows - 1; i++)
		{
			auto col1 = m_cells[i][col - 1];
			auto col2 = m_cells[i + 1][col - 1];
			bool needSwitch = false;
			if (!col1 && !col2)continue;
			if (col1 && !col2)continue;
			if (!col1 && col2)needSwitch = true;
			if (col1 && col2)
			{
				if (col1->GetType() == CellType::Number && col2->GetType() == CellType::Number)
				{
					needSwitch = col2->celldataN < col1->celldataN;
				}
				if (col1->GetType() == CellType::Number && col2->GetType() == CellType::String)
				{
					needSwitch = false;
				}
				if (col1->GetType() == CellType::String && col2->GetType() == CellType::Number)
				{
					needSwitch = true;
				}
				if (col1->GetType() == CellType::String && col2->GetType() == CellType::String)
				{
					needSwitch = col2->celldataS < col1->celldataS;
				}

			}
			if (needSwitch)
			{
				flag = true;
				auto temp = m_cells[i];
				m_cells[i] = m_cells[i + 1];
				m_cells[i + 1] = temp;
				//ExportSheet(std::cout);
			}
		}
		if (!flag)return;
	}
}

int main()
{
	SpreadSheet sheet(5, 5);
	sheet.UpdateCell(1, 1, new NumberSpreadSheetCell(1.1));
	sheet.UpdateCell(4, 1, new NumberSpreadSheetCell(0.5));
	sheet.UpdateCell(1, 3, new NumberSpreadSheetCell(3.4));
	sheet.UpdateCell(2, 4, new StringSpreadSheetCell("foo"));
	sheet.UpdateCell(3, 1, new StringSpreadSheetCell("bar"));
	sheet.UpdateCell(3, 2, new StringSpreadSheetCell("baz"));
	sheet.UpdateCell(4, 2, new NumberSpreadSheetCell(0));
	sheet.UpdateCell(5, 1, new StringSpreadSheetCell("raz"));
	//sheet.HideColumn(3);
	//sheet.HideRow(2);
	sheet.SortByColumn(1);
	sheet.ExportSheet(std::cout);
	return 0;
}
