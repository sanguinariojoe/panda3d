/**
 * PANDA 3D SOFTWARE
 * Copyright (c) Carnegie Mellon University.  All rights reserved.
 *
 * All use of this software is subject to the terms of the revised BSD
 * license.  You should have received a copy of this license along
 * with this source code in a file named "LICENSE."
 *
 * @file bulletTriangleMeshShape.I
 * @author enn0x
 * @date 2010-02-09
 */

/**
 *
 */
INLINE BulletTriangleMeshShape::
BulletTriangleMeshShape(const BulletTriangleMeshShape &copy) :
  _bvh_shape(copy._bvh_shape),
  _gimpact_shape(copy._gimpact_shape),
  _mesh(copy._mesh) {
}

/**
 *
 */
INLINE void BulletTriangleMeshShape::
operator = (const BulletTriangleMeshShape &copy) {

  _bvh_shape = copy._bvh_shape;
  _gimpact_shape = copy._gimpact_shape;
  _mesh = copy._mesh;
}

/**
 *
 */
INLINE BulletTriangleMeshShape::
~BulletTriangleMeshShape() {

  if (_bvh_shape) {
    delete _bvh_shape;
  }

  if (_gimpact_shape) {
    delete _gimpact_shape;
  }
}

/**
 *
 */
INLINE bool BulletTriangleMeshShape::
is_static() const {

  return (_bvh_shape != NULL);
}

/**
 *
 */
INLINE bool BulletTriangleMeshShape::
is_dynamic() const {

  return (_gimpact_shape != NULL);
}
