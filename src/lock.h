/*
Copyright 2013 Michael Curran <mick@nvaccess.org>.
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License version 2.1, as published by
    the Free Software Foundation.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
This license can be found at:
http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html
*/

#ifndef NVDAHELPER_LOCK_H
#define NVDAHELPER_LOCK_H

#include <cassert>
#include <windows.h>

/**
 * A class that provides a locking mechonism on objects.
 * The lock is reeentrant for the same thread.
 */
class LockableObject {
	private:
	CRITICAL_SECTION _cs;

	public:

	LockableObject() {
		InitializeCriticalSection(&_cs);
	}

	virtual ~LockableObject() {
		DeleteCriticalSection(&_cs);
	}

/**
 * Acquires access (possibly waighting until its free).
 */
	void acquire() {
	EnterCriticalSection(&_cs);
}

/**
 * Releases exclusive access of the object.
 */
	void release() {
		LeaveCriticalSection(&_cs);
	}

};

/**
 * A class providing both exclusive locking, and reference counting with auto-deletion.
 * Do not use this in multiple inheritence.
 */
class LockableAutoFreeObject: private LockableObject {
	private:
	volatile long _refCount;

	protected:

long incRef() {
		return InterlockedIncrement(&_refCount);
	}

	long decRef() {
		long refCount=InterlockedDecrement(&_refCount);
		if(refCount==0) {
			delete this;
		}
		assert(refCount>=0);
		return refCount;
	}

	public:

	LockableAutoFreeObject(): _refCount(1) {
	}

/**
 * Increases the reference count and acquires exclusive access.
 */
	void acquire() {
		incRef();
		LockableObject::acquire();
	}

	void release() {
		LockableObject::release();
		decRef();
	}

/**
 * Deletes this object if no one has acquired it, or indicates that it should be deleted once it has been released.
 */
	void requestDelete() {
		decRef();
	}

};

#endif