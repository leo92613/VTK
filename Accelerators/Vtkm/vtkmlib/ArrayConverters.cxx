//=============================================================================
//
//  Copyright (c) Kitware, Inc.
//  All rights reserved.
//  See LICENSE.txt for details.
//
//  This software is distributed WITHOUT ANY WARRANTY; without even
//  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
//  PURPOSE.  See the above copyright notice for more information.
//
//  Copyright 2012 Sandia Corporation.
//  Under the terms of Contract DE-AC04-94AL85000 with Sandia Corporation,
//  the U.S. Government retains certain rights in this software.
//
//=============================================================================
#include "ArrayConverters.h"

#include "Storage.h"
#include "vtkmDataArray.h"
#include "vtkmFilterPolicy.h"

#include <vtkm/cont/ArrayHandle.h>
#include <vtkm/cont/ArrayHandleVirtual.h>
#include <vtkm/cont/CoordinateSystem.hxx>
#include <vtkm/cont/DataSet.h>

#include "vtkCellData.h"
#include "vtkDataArray.h"
#include "vtkDataObject.h"
#include "vtkDataSet.h"
#include "vtkPointData.h"
#include "vtkPoints.h"
#include "vtkTypedDataArray.h"

namespace tovtkm {

void ProcessFields(vtkDataSet *input, vtkm::cont::DataSet &dataset,
                   tovtkm::FieldsFlag fields)
{
  if ((fields & tovtkm::FieldsFlag::Points) != tovtkm::FieldsFlag::None)
  {
    vtkPointData* pd = input->GetPointData();
    for (int i = 0; i < pd->GetNumberOfArrays(); i++)
    {
      vtkDataArray* array = pd->GetArray(i);
      if (array == nullptr)
      {
        continue;
      }

      vtkm::cont::Field pfield =
          tovtkm::Convert(array, vtkDataObject::FIELD_ASSOCIATION_POINTS);
      dataset.AddField(pfield);
    }
  }

  if ((fields & tovtkm::FieldsFlag::Cells) != tovtkm::FieldsFlag::None)
  {
    vtkCellData* cd = input->GetCellData();
    for (int i = 0; i < cd->GetNumberOfArrays(); i++)
    {
      vtkDataArray* array = cd->GetArray(i);
      if (array == nullptr)
      {
        continue;
      }

      vtkm::cont::Field cfield =
          tovtkm::Convert(array, vtkDataObject::FIELD_ASSOCIATION_CELLS);
      dataset.AddField(cfield);
    }
  }
}

template <typename DataArrayType>
vtkm::cont::Field ConvertPointField(DataArrayType* input)
{
  typedef typename DataArrayType::ValueType ValueType;
  typedef
      typename tovtkm::ArrayContainerTagType<DataArrayType>::TagType TagType;
  // We know the ValueType now, so all that is left is to deduce
  // the number of components
  int numComps = input->GetNumberOfComponents();
  std::string name(input->GetName());
  switch (numComps)
  {
  case 1:
  {
    typedef ValueType VType;
    typedef vtkm::cont::internal::Storage<VType, TagType> StorageType;
    StorageType storage(input);
    vtkm::cont::ArrayHandle<VType, TagType> handle(storage);
    vtkm::cont::VariantArrayHandle vhandle(handle);
    return vtkm::cont::Field(name, vtkm::cont::Field::Association::POINTS, vhandle);
  }
  case 2:
  {
    typedef vtkm::Vec<ValueType, 2> VType;
    typedef vtkm::cont::internal::Storage<VType, TagType> StorageType;
    StorageType storage(input);
    vtkm::cont::ArrayHandle<VType, TagType> handle(storage);
    vtkm::cont::VariantArrayHandle vhandle(handle);
    return vtkm::cont::Field(name, vtkm::cont::Field::Association::POINTS, vhandle);
  }
  case 3:
  {
    typedef vtkm::Vec<ValueType, 3> VType;
    typedef vtkm::cont::internal::Storage<VType, TagType> StorageType;
    StorageType storage(input);
    vtkm::cont::ArrayHandle<VType, TagType> handle(storage);
    vtkm::cont::VariantArrayHandle vhandle(handle);
    return vtkm::cont::Field(name, vtkm::cont::Field::Association::POINTS, vhandle);
  }
  case 4:
  {
    typedef vtkm::Vec<ValueType, 4> VType;
    typedef vtkm::cont::internal::Storage<VType, TagType> StorageType;
    StorageType storage(input);
    vtkm::cont::ArrayHandle<VType, TagType> handle(storage);
    vtkm::cont::VariantArrayHandle vhandle(handle);
    return vtkm::cont::Field(name, vtkm::cont::Field::Association::POINTS, vhandle);
  }
  default:
    break;
  }
  return vtkm::cont::Field();
}

template <typename DataArrayType>
vtkm::cont::Field ConvertCellField(DataArrayType* input)
{
  typedef typename DataArrayType::ValueType ValueType;
  typedef
      typename tovtkm::ArrayContainerTagType<DataArrayType>::TagType TagType;
  // We know the ValueType now, so all that is left is to deduce
  // the number of components
  int numComps = input->GetNumberOfComponents();
  std::string name(input->GetName());

  // todo: FIX-ME
  // currently you can't get the name of a dynamic cell set so we just use
  // the default name
  // cellset.CastAndCall();
  std::string cname("cells");
  switch (numComps)
  {
  case 1:
  {
    typedef ValueType VType;
    typedef vtkm::cont::internal::Storage<VType, TagType> StorageType;
    StorageType storage(input);
    vtkm::cont::ArrayHandle<VType, TagType> handle(storage);
    vtkm::cont::VariantArrayHandle vhandle(handle);
    return vtkm::cont::Field(name, vtkm::cont::Field::Association::CELL_SET, cname,
                             vhandle);
  }
  case 2:
  {
    typedef vtkm::Vec<ValueType, 2> VType;
    typedef vtkm::cont::internal::Storage<VType, TagType> StorageType;
    StorageType storage(input);
    vtkm::cont::ArrayHandle<VType, TagType> handle(storage);
    vtkm::cont::VariantArrayHandle vhandle(handle);
    return vtkm::cont::Field(name, vtkm::cont::Field::Association::CELL_SET, cname,
                             vhandle);
  }
  case 3:
  {
    typedef vtkm::Vec<ValueType, 3> VType;
    typedef vtkm::cont::internal::Storage<VType, TagType> StorageType;
    StorageType storage(input);
    vtkm::cont::ArrayHandle<VType, TagType> handle(storage);
    vtkm::cont::VariantArrayHandle vhandle(handle);
    return vtkm::cont::Field(name, vtkm::cont::Field::Association::CELL_SET, cname,
                             vhandle);
  }
  case 4:
  {
    typedef vtkm::Vec<ValueType, 4> VType;
    typedef vtkm::cont::internal::Storage<VType, TagType> StorageType;
    StorageType storage(input);
    vtkm::cont::ArrayHandle<VType, TagType> handle(storage);
    vtkm::cont::VariantArrayHandle vhandle(handle);
    return vtkm::cont::Field(name, vtkm::cont::Field::Association::CELL_SET, cname,
                             vhandle);
  }
  default:
    break;
  }
  return vtkm::cont::Field();
}

template <typename DataArrayType>
vtkm::cont::Field Convert(DataArrayType* input, int association)
{
  // we need to switch on if we are a cell or point field first!
  // The problem is that the constructor signature for fields differ based
  // on if they are a cell or point field.
  if (association == vtkDataObject::FIELD_ASSOCIATION_POINTS)
  {
    return ConvertPointField(input);
  }
  else if (association == vtkDataObject::FIELD_ASSOCIATION_CELLS)
  {
    return ConvertCellField(input);
  }

  return vtkm::cont::Field();
}

template <typename T>
vtkm::cont::Field Convert(vtkmDataArray<T>* input, int association)
{
  // we need to switch on if we are a cell or point field first!
  // The problem is that the constructor signature for fields differ based
  // on if they are a cell or point field.
  if (association == vtkDataObject::FIELD_ASSOCIATION_POINTS)
  {
    return vtkm::cont::Field(input->GetName(), vtkm::cont::Field::Association::POINTS,
                             input->GetVtkmVariantArrayHandle());
  }
  else if (association == vtkDataObject::FIELD_ASSOCIATION_CELLS)
  {
    return vtkm::cont::Field(input->GetName(), vtkm::cont::Field::Association::CELL_SET, "cells",
                             input->GetVtkmVariantArrayHandle());
  }

  return vtkm::cont::Field();
}

// determine the type and call the proper Convert routine
vtkm::cont::Field Convert(vtkDataArray* input, int association)
{
  // The association will tell us if we have a cell or point field

  // We need to properly deduce the ValueType of the array. This means
  // that we need to switch on Float/Double/Int, and then figure out the
  // number of components. The upside is that the Convert Method can internally
  // figure out the number of components, and not have to generate a lot
  // of template to do so

  // Investigate using vtkArrayDispatch, AOS for all types, and than SOA for
  // just
  // float/double
  vtkm::cont::Field field;
  switch (input->GetDataType())
  {
    vtkTemplateMacro(
        vtkAOSDataArrayTemplate<VTK_TT>* typedIn1 =
            vtkAOSDataArrayTemplate<VTK_TT>::FastDownCast(input);
        if (typedIn1) { field = Convert(typedIn1, association); }
        else {
          vtkSOADataArrayTemplate<VTK_TT>* typedIn2 =
              vtkSOADataArrayTemplate<VTK_TT>::FastDownCast(input);
          if (typedIn2) { field = Convert(typedIn2, association); }
          else {
            vtkmDataArray<VTK_TT>* typedIn3 =
                vtkmDataArray<VTK_TT>::SafeDownCast(input);
            if (typedIn3) { field = Convert(typedIn3, association); }
          }
        });
    // end vtkTemplateMacro
  }
  return field;
}

} // namespace tovtkm

namespace fromvtkm {

namespace {

struct ArrayConverter
{
public:
  mutable vtkDataArray* Data;

  ArrayConverter() : Data(nullptr) {}

  // CastAndCall always passes a const array handle. Just shallow copy to a
  // local array handle by taking by value.

  template <typename T, typename S>
  void operator()(vtkm::cont::ArrayHandle<T, S> handle) const
  {
    this->Data = make_vtkmDataArray(handle);
  }

  template <typename T>
  void operator()(vtkm::cont::ArrayHandle<T, vtkm::cont::StorageTagVirtual> handle) const
  {
    using AOSHandle = vtkm::cont::ArrayHandle<T, tovtkm::vtkAOSArrayContainerTag>;
    using SOAHandle = vtkm::cont::ArrayHandle<T, tovtkm::vtkSOAArrayContainerTag>;
    using BasicHandle = vtkm::cont::ArrayHandle<T, vtkm::cont::StorageTagBasic>;
    if (vtkm::cont::IsType<AOSHandle>(handle))
    {
      this->operator()( vtkm::cont::Cast<AOSHandle>(handle) );
    }
    else if(vtkm::cont::IsType<SOAHandle>(handle))
    {
      this->operator()( vtkm::cont::Cast<SOAHandle>(handle) );
    }
    else if(vtkm::cont::IsType<BasicHandle>(handle))
    {
      this->operator()( vtkm::cont::Cast<BasicHandle>(handle) );
    }
    else
    {
      this->Data = make_vtkmDataArray(handle);
    }
  }


  template <typename T>
  void operator()(
    vtkm::cont::ArrayHandle<T, vtkm::cont::StorageTagBasic> handle) const
  {
    // we can steal this array!
    using Traits = tovtkm::vtkPortalTraits<T>; //Handles Vec<Vec<T,N,N> properly
    using ValueType = typename Traits::ComponentType;
    using VTKArrayType = vtkAOSDataArrayTemplate<ValueType>;

    VTKArrayType* array = VTKArrayType::New();
    array->SetNumberOfComponents(Traits::NUM_COMPONENTS);

    handle.SyncControlArray();
    const vtkm::Id size = handle.GetNumberOfValues() * Traits::NUM_COMPONENTS;

    //stealing the array clears the delete function, so we need to get the function first.
    //VTK-m allocations are aligned or done with cuda uvm memory so we need to propagate
    //the proper free function to VTK
    auto stolenState = handle.GetStorage().StealArray();
    auto stolenMemory = reinterpret_cast<ValueType*>(stolenState.first);
    array->SetVoidArray(
      stolenMemory, size, 0, vtkAbstractArray::VTK_DATA_ARRAY_USER_DEFINED);
    array->SetArrayFreeFunction(stolenState.second);

    this->Data = array;
  }

  template <typename T>
  void operator()(
    vtkm::cont::ArrayHandle<T, tovtkm::vtkAOSArrayContainerTag> handle) const
  {
    // we can grab the already allocated vtk memory
    this->Data = handle.GetStorage().VTKArray();
    this->Data->Register(nullptr);
  }

  template <typename T>
  void operator()(
    vtkm::cont::ArrayHandle<T, tovtkm::vtkSOAArrayContainerTag> handle) const
  {
    // we can grab the already allocated vtk memory
    this->Data = handle.GetStorage().VTKArray();
    this->Data->Register(nullptr);
  }
};
} // anonymous namespace

// Though the following conversion routines take const-ref parameters as input,
// the underlying storage will be stolen, whenever possible, instead of
// performing a full copy.
// Therefore, these routines should be treated as "moves" and the state of the
// input is undeterminisitic.

vtkDataArray* Convert(const vtkm::cont::Field& input)
{
  // We need to do the conversion from Field to a known vtkm::cont::ArrayHandle
  // after that we need to fill the vtkDataArray
  vtkmOutputFilterPolicy policy;
  vtkDataArray* data = nullptr;
  ArrayConverter aConverter;

  try
  {
    vtkm::cont::CastAndCall(vtkm::filter::ApplyPolicy(input, policy),
                            aConverter);
    data = aConverter.Data;
    if (data)
    {
      data->SetName(input.GetName().c_str());
    }
  }
  catch (vtkm::cont::Error&)
  {
  }
  return data;
}

vtkPoints* Convert(const vtkm::cont::CoordinateSystem& input)
{
  ArrayConverter aConverter;
  vtkPoints* points = nullptr;
  try
  {
    vtkm::cont::CastAndCall(input, aConverter);
    vtkDataArray* pdata = aConverter.Data;
    points = vtkPoints::New();
    points->SetData(pdata);
    pdata->FastDelete();
  }
  catch (vtkm::cont::Error &e)
  {
    vtkGenericWarningMacro("Converting vtkm::cont::CoordinateSystem to "
                           "vtkPoints failed: " << e.what());
  }
  return points;
}

bool ConvertArrays(const vtkm::cont::DataSet& input, vtkDataSet* output)
{
  vtkPointData* pd = output->GetPointData();
  vtkCellData* cd = output->GetCellData();

  vtkm::IdComponent numFields = input.GetNumberOfFields();
  for (vtkm::IdComponent i = 0; i < numFields; ++i)
  {
    const vtkm::cont::Field& f = input.GetField(i);
    vtkDataArray* vfield = Convert(f);
    if (vfield && f.GetAssociation() == vtkm::cont::Field::Association::POINTS)
    {
      pd->AddArray(vfield);
      vfield->FastDelete();
    }
    else if (vfield &&  f.GetAssociation() == vtkm::cont::Field::Association::CELL_SET)
    {
      cd->AddArray(vfield);
      vfield->FastDelete();
    }
    else if(vfield)
    {
      vfield->Delete();
    }
  }
  return true;
}
}
