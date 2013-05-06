/** \file
 *  Game Develop
 *  2008-2013 Florian Rival (Florian.Rival@gmail.com)
 */
#ifndef EVENTSCODEGENERATIONCONTEXT_H
#define EVENTSCODEGENERATIONCONTEXT_H

#include <string>
#include <set>
#include <boost/shared_ptr.hpp>
namespace gd { class Layout; }

namespace gd
{

/**
 * Used to manage the context ( objects concerned, objects being modified by an action... )
 * when generating code for events.
 */
class GD_CORE_API EventsCodeGenerationContext
{
    friend class EventsCodeGenerator;
public:
    /**
     * Default constructor. You may want to call InheritsFrom just after.
     */
    EventsCodeGenerationContext() {};
    virtual ~EventsCodeGenerationContext() {};

    /**
     * Call this method to make an EventsCodeGenerationContext as a "child" of another one.
     * The child will then for example not declare again objects already declared by its parent.
     */
    void InheritsFrom(const EventsCodeGenerationContext & parent);

    /**
     * Mark the object has being the object being handled by the instruction
     */
    void SetCurrentObject(const std::string & objectName) { currentObject = objectName; };

    /**
     * Set that no particular object is being handled by an instruction
     */
    void SetNoCurrentObject() { currentObject = ""; };

    /**
     * Get the object being handled by the instruction
     */
    const std::string & GetCurrentObject() const { return currentObject; };

    /**
     * Call this when an instruction in the event need an object list.
     * The list will be filled with objects from the scene if it is the first time it is requested.
     */
    void ObjectsListNeeded(const std::string & objectName);

    /**
     * Call this when an instruction in the event need an object list.
     * No object will be picked from the scene.
     */
    void EmptyObjectsListNeeded(const std::string & objectName);

    /**
     * Return true if an object list has already been declared ( or is going to be declared ).
     */
    bool ObjectAlreadyDeclared(const std::string & objectName) { return (alreadyDeclaredObjectsLists.find(objectName) != alreadyDeclaredObjectsLists.end()); };

    /**
     * Consider that \a objectName is now declared in the context.
     */
    void SetObjectDeclared(const std::string & objectName ) { alreadyDeclaredObjectsLists.insert(objectName); }

    /**
     * Return all the objects lists which will be declared by the current context
     * ( the non empty as well as the empty objects lists )
     */
    std::set<std::string> GetAllObjectsToBeDeclared();

    /**
     * Return the objects lists which will be declared by the current context
     */
    const std::set<std::string> & GetObjectsListsToBeDeclared() { return objectsListsToBeDeclared; };

    /**
     * Return the objects lists which will be declared, but no filled, by the current context
     */
    const std::set<std::string> & GetObjectsListsToBeDeclaredEmpty() { return emptyObjectsListsToBeDeclared; };

private:
    std::set<std::string> alreadyDeclaredObjectsLists;
    std::set<std::string> objectsListsToBeDeclared;
    std::set<std::string> emptyObjectsListsToBeDeclared;
    std::string currentObject;
};

}
#endif // EVENTSCODEGENERATIONCONTEXT_H