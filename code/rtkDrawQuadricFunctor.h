/*=========================================================================
 *
 *  Copyright RTK Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#ifndef __rtkDrawQuadricFunctor_h
#define __rtkDrawQuadricFunctor_h

#include <itkInPlaceImageFilter.h>
#include <itkImageFileWriter.h>

#include "rtkThreeDCircularProjectionGeometry.h"
#include "rtkRayQuadricIntersectionImageFilter.h"
#include "rtkThreeDCircularProjectionGeometryXMLFile.h"
#include "rtkSheppLoganPhantomFilter.h"

#include <vector>

namespace rtk
{

/** \class DrawQuadricFunctor
 * \brief Computes the 3D reference of an specefic quadric surface.
 */

template <class TInputImage, class TOutputImage>
class ITK_EXPORT DrawQuadricFunctor :
  public itk::InPlaceImageFilter<TInputImage,TOutputImage>
{
public:
  /** Standard class typedefs. */
  typedef DrawQuadricFunctor                                        Self;
  typedef itk::InPlaceImageFilter<TInputImage,TOutputImage>              Superclass;
  typedef itk::SmartPointer<Self>                                   Pointer;
  typedef itk::SmartPointer<const Self>                             ConstPointer;
  typedef typename TOutputImage::RegionType                         OutputImageRegionType;
  typedef typename TOutputImage::Superclass::ConstPointer           OutputImageBaseConstPointer;

  typedef float OutputPixelType;

  typedef itk::Image< OutputPixelType, 3 >                          OutputImageType;
  typedef std::vector<double>                                       VectorType;
  typedef std::string                                               StringType;

  typedef rtk::SetQuadricParamFromRegularParamFunction              SQPFunctionType;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(DrawQuadricFunctor, InPlaceImageFilter);

  /** Get/Set ConfigFile*/
  itkSetMacro(ConfigFile, StringType);
  itkGetMacro(ConfigFile, StringType);

protected:
  DrawQuadricFunctor() {}
  virtual ~DrawQuadricFunctor() {};

  virtual void ThreadedGenerateData( const OutputImageRegionType& outputRegionForThread, ThreadIdType threadId );
  /** Translate user parameteres to quadric parameters.
   * A call to this function will assume modification of the function.*/


private:
  DrawQuadricFunctor(const Self&); //purposely not implemented
  void operator=(const Self&);            //purposely not implemented
  SQPFunctionType::Pointer m_SQPFunctor;
  StringType m_ConfigFile;

};

} // end namespace rtk

#ifndef ITK_MANUAL_INSTANTIATION
#include "rtkDrawQuadricFunctor.txx"
#endif

#endif


