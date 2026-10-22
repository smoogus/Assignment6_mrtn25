#include <iostream>
#include <cstdlib>
#include <ctime>
#include "coordinate.h"

using namespace std;

static float random_coord()
{
  return (float)rand() / RAND_MAX * 100.0f;   // 0.0 to 100.0
}

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    cout << "Usage: " << argv[0] << " <number of coordinates>\n";
    return 1;
  }

  int n = atoi(argv[1]);
  if (n < 1)
  {
    cout << "Please enter a positive number.\n";
    return 1;
  }

  srand((unsigned)time(nullptr));

  // Create the first node by hand, then add the rest
  Coordinate *head = new Coordinate;
  head->x = random_coord();
  head->y = random_coord();
  head->coord_id = 0;
  head->next = nullptr;
  head->previous = nullptr;

  Coordinate *end = head;
  for (int i = 1; i < n; i++)
  {
    add_coordinate(end, random_coord(), random_coord());
    end = end->next;
  }

  cout << "List length: " << list_length(head) << "\n\n";

  cout << "Forward:\n";
  forward_display(head);
  cout << "\nBackward:\n";
  backward_display(end);

  cout << "\n";
  closest_to(head, 50.0f, 50.0f);

  // Delete a coordinate (just supply a value)
  int to_delete = (n > 2) ? 2 : 0;
  cout << "\nDeleting ID " << to_delete << "...\n";
  delete_coordinate(head, to_delete);

  // The end node may have been deleted/changed, so find it again
  end = head;
  while (end->next != nullptr)
    end = end->next;

  cout << "\nAfter delete (forward):\n";
  forward_display(head);
  cout << "List length: " << list_length(head) << "\n";

  // Free everything
  while (head != nullptr)
  {
    Coordinate *next = head->next;
    delete head;
    head = next;
  }

  return 0;
}
