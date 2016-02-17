/**
 * PANDA 3D SOFTWARE
 * Copyright (c) Carnegie Mellon University.  All rights reserved.
 *
 * All use of this software is subject to the terms of the revised BSD
 * license.  You should have received a copy of this license along
 * with this source code in a file named "LICENSE."
 *
 * @file mouseRecorder.h
 * @author drose
 * @date 2004-01-25
 */

#ifndef MOUSERECORDER_H
#define MOUSERECORDER_H

#include "recorderBase.h"
#include "dataNode.h"
#include "dataNodeTransmit.h"
#include "linmath_events.h"
#include "buttonEventList.h"

class FactoryParams;
class BamReader;
class BamWriter;

/**
 * This object records any data generated by a particular MouseAndKeyboard
 * node on the datagraph for a session for eventual playback via a
 * DataGraphPlayback (and a PlaybackController).  To use it, make it a child
 * of the node you wish to record.  It also serves as a pass-through, so that
 * additional child nodes may be parented directly to it.
 */
class EXPCL_PANDA_RECORDER MouseRecorder : public DataNode, public RecorderBase {
PUBLISHED:
  MouseRecorder(const string &name);
  virtual ~MouseRecorder();

public:
  virtual void record_frame(BamWriter *manager, Datagram &dg);
  virtual void play_frame(DatagramIterator &scan, BamReader *manager);

public:
  virtual void output(ostream &out) const;
  virtual void write(ostream &out, int indent_level = 0) const;

protected:
  // Inherited from DataNode
  virtual void do_transmit_data(DataGraphTraverser *trav,
                                const DataNodeTransmit &input,
                                DataNodeTransmit &output);

private:
  // inputs
  int _pixel_xy_input;
  int _pixel_size_input;
  int _xy_input;
  int _button_events_input;

  // outputs
  int _pixel_xy_output;
  int _pixel_size_output;
  int _xy_output;
  int _button_events_output;

  bool _has_mouse;
  LPoint2 _mouse_xy;
  LPoint2 _mouse_pixel_xy;
  PT(ButtonEventList) _live_button_events;
  PT(ButtonEventList) _save_button_events;

  PT(EventStoreVec2) _pixel_xy;
  PT(EventStoreVec2) _xy;

public:
  static void register_with_read_factory();
  virtual void write_datagram(BamWriter *manager, Datagram &dg);
  virtual void write_recorder(BamWriter *manager, Datagram &dg);

  INLINE virtual void ref() const FINAL { ReferenceCount::ref(); };
  INLINE virtual bool unref() const FINAL { return ReferenceCount::unref(); };

protected:
  static TypedWritable *make_from_bam(const FactoryParams &params);
  static RecorderBase *make_recorder(const FactoryParams &params);
  void fillin(DatagramIterator &scan, BamReader *manager);
  void fillin_recorder(DatagramIterator &scan, BamReader *manager);

public:
  static TypeHandle get_class_type() {
    return _type_handle;
  }
  static void init_type() {
    DataNode::init_type();
    RecorderBase::init_type();
    register_type(_type_handle, "MouseRecorder",
                  DataNode::get_class_type(),
                  RecorderBase::get_class_type());
  }
  virtual TypeHandle get_type() const {
    return get_class_type();
  }
  virtual TypeHandle force_init_type() {init_type(); return get_class_type();}

private:
  static TypeHandle _type_handle;
};

#endif
