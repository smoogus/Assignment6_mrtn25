#include <iostream>
#include <cmath>
#include "coordinate.h"

using namespace std;

void add_coordinate(Coordinate *list_end, float x, float y)
{
  // length of the list = number of nodes from list_end back to the start
  int length = 0;
  for (Coordinate *p = list_end; p != nullptr; p = p->previous)
    length++;

  Coordinate *node = new Coordinate;
  node->x = x;
  node->y = y;
  node->coord_id = length;       // 0-based: first node is 0, next is 1, ...
  node->next = nullptr;
  node->previous = list_end;
  list_end->next = node;
}

void forward_display(Coordinate *list_beginning)
{
  for (Coordinate *p = list_beginning; p != nullptr; p = p->next)
    cout << "ID " << p->coord_id << ": (" << p->x << ", " << p->y << ")\n";
}

void backward_display(Coordinate *list_end)
{
  for (Coordinate *p = list_end; p != nullptr; p = p->previous)
    cout << "ID " << p->coord_id << ": (" << p->x << ", " << p->y << ")\n";
}

void delete_coordinate(Coordinate *list_beginning, int coord_id_to_delete)
{
  Coordinate *p = list_beginning;
  while (p != nullptr && p->coord_id != coord_id_to_delete)
    p = p->next;

  if (p == nullptr)
  {
    cout << "Coordinate with ID " << coord_id_to_delete << " not found.\n";
    return;
  }

  // Deleting the head: the caller's pointer to the head must stay valid
  // (function returns void), so copy the second node into the head
  // and free the second node instead.
  if (p == list_beginning)
  {
    Coordinate *second = p->next;
    if (second == nullptr)
    {
      cout << "Cannot delete the only node in the list.\n";
      return;
    }
    p->x = second->x;
    p->y = second->y;
    p->coord_id = second->coord_id;
    p->next = second->next;
    if (second->next != nullptr)
      second->next->previous = p;
    delete second;
    return;
  }

  p->previous->next = p->next;
  if (p->next != nullptr)
    p->next->previous = p->previous;
  delete p;
}

int list_length(Coordinate *list_beginning)
{
  int length = 0;
  for (Coordinate *p = list_beginning; p != nullptr; p = p->next)
    length++;
  return length;
}

void closest_to(Coordinate *list_beginning, float x, float y)
{
  if (list_beginning == nullptr)
  {
    cout << "List is empty.\n";
    return;
  }

  Coordinate *closest = list_beginning;
  float best = sqrt((list_beginning->x - x) * (list_beginning->x - x) +
                    (list_beginning->y - y) * (list_beginning->y - y));

  for (Coordinate *p = list_beginning->next; p != nullptr; p = p->next)
  {
    float d = sqrt((p->x - x) * (p->x - x) + (p->y - y) * (p->y - y));
    if (d < best)
    {
      best = d;
      closest = p;
    }
  }

  cout << "Closest to (" << x << ", " << y << ") is ID " << closest->coord_id
       << " at (" << closest->x << ", " << closest->y << "), distance "
       << best << "\n";
}
