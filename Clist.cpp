// ÏĞÎÅÊÒ:     Ìàòåìàòè÷åñêàÿ ìîäåëü ÈÌÏÓËÜÑ
// ÂÅĞÑÈß:     1.0
// ÔÀÉË:       CList.CPP
// ÄÀÒÀ:       6/95
// ÀÂÒÎĞ:      Øòèôàíîâ À.È.
// ÑÎÄÅĞÆÀÍÈÅ:

#include "impulse.hpp"

// ÊËÀÑÑ: CList ------------------------

CElement *CList :: Add(CElement *newElement)
 {
  // See if it is a default insertion.
  if (!first) return (CList::Add(0, newElement));

  // Insert at beginning of the list.
  newElement->previous = 0;
  newElement->next = first;
  first->previous = newElement;
  first = newElement;

  // Return a pointer to the element.
  return (newElement);
 }


CElement *CList :: Add(CElement *element, CElement *newElement)
 {
  // Add the element to the list.
  if (!first)   {
     newElement->previous = newElement->next = 0;
     first = last = newElement;
  }
  else if (!element)   {
     newElement->previous = last;
     newElement->next = 0;
     last->next = newElement;
     last = newElement;
  }
  else   {
     newElement->previous = element->previous;
     newElement->next = element;
     if (!element->previous)  first = newElement;
     else                     element->previous->next = newElement;
     element->previous = newElement;
  }

  // Return a pointer to the element.
  return (newElement);
}


CElement *CList :: Subtract(CElement *element)
{
  CElement *tElement = element;

  // Make sure the element is in the list.
  while (tElement->previous)   tElement = tElement->previous;
  if (tElement != first)       return (element);

  // Delete the specified element from the list.
  if (element->previous)  element->previous->next = element->next;
  else	                  first = element->next;

  if (element->next)   	  element->next->previous = element->previous;
  else                    last = element->previous;

  if (current == element) current = first;

  // Return the next element.
  return (element->next);
}


int CList :: Count()
{
  int count = 0;

  // Get the element index.
  for (CElement *element = first; element; element = element->next) count++;

  // Return the count.
  return (count);
}


void CList :: Destroy()
{
 CElement *tElement;

 // Delete all the elements in the list.
 for (CElement *element = first; element; )  {
    tElement = element;
    element = element->next;
    delete tElement;
 }
 first = last = current = 0;
}


CElement *CList :: Get(int index)
{
 CElement *element;
 // Get the list element.
 for (element = first; index && element; element = element->next)
    index--;

 // Return the element.
 return (element);
}


int CList :: Index(const CElement *element)
{
 CElement *tElement;
 // Get the element index.
 int index = 0;
 for (tElement = first;
      tElement && tElement != element;
      tElement = tElement->next)
    index++;

 // Return the index.
 if (tElement)	return (index);

 return (-1);
}



