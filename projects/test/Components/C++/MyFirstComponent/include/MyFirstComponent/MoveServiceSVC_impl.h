// -*-C++-*-
/*!
 * @file  MoveServiceSVC_impl.h
 * @brief Service implementation header of MoveService.idl
 *
 */

#include "BasicDataTypeSkel.h"

#include "MoveServiceSkel.h"

#ifndef MOVESERVICESVC_IMPL_H
#define MOVESERVICESVC_IMPL_H
 
/*!
 * @class MoveServiceSVC_impl
 * Example class implementing IDL interface MoveService
 */
class MoveServiceSVC_impl
 : public virtual POA_MoveService,
   public virtual PortableServer::RefCountServantBase
{
 private:
   // Make sure all instances are built on the heap by making the
   // destructor non-public
   //virtual ~MoveServiceSVC_impl();

 public:
  /*!
   * @brief standard constructor
   */
   MoveServiceSVC_impl();
  /*!
   * @brief destructor
   */
   virtual ~MoveServiceSVC_impl();

   // attributes and operations
   void drive(CORBA::Short leftWheel, CORBA::Short rightWheel);

};



#endif // MOVESERVICESVC_IMPL_H


