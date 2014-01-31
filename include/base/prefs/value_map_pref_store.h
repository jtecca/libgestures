// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_PREFS_VALUE_MAP_PREF_STORE_H_
#define BASE_PREFS_VALUE_MAP_PREF_STORE_H_

#include <map>
#include <string>

#include "base/basictypes.h"
#include "base/observer_list.h"
#include "base/prefs/pref_store.h"
#include "base/prefs/pref_value_map.h"

// A basic PrefStore implementation that uses a simple name-value map for
// storing the preference values.
class ValueMapPrefStore : public PrefStore {
 public:
  typedef std::map<std::string, base::Value*>::iterator iterator;
  typedef std::map<std::string, base::Value*>::const_iterator const_iterator;

  ValueMapPrefStore();

  // PrefStore overrides:
  virtual ReadResult GetValue(const std::string& key,
                              const base::Value** value) const OVERRIDE;
  virtual void AddObserver(PrefStore::Observer* observer) OVERRIDE;
  virtual void RemoveObserver(PrefStore::Observer* observer) OVERRIDE;
  virtual size_t NumberOfObservers() const OVERRIDE;

  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;

 protected:
  virtual ~ValueMapPrefStore();

  // Store a |value| for |key| in the store. Also generates an notification if
  // the value changed. Assumes ownership of |value|, which must be non-NULL.
  void SetValue(const std::string& key, base::Value* value);

  // Remove the value for |key| from the store. Sends a notification if there
  // was a value to be removed.
  void RemoveValue(const std::string& key);

  // Notify observers about the initialization completed event.
  void NotifyInitializationCompleted();

 private:
  PrefValueMap prefs_;

  ObserverList<PrefStore::Observer, true> observers_;

  DISALLOW_COPY_AND_ASSIGN(ValueMapPrefStore);
};

#endif  // BASE_PREFS_VALUE_MAP_PREF_STORE_H_