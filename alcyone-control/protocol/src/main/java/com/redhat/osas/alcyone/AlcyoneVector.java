package com.redhat.osas.alcyone;

/**
 * User: jottinge
 * Date: 4/1/13
 * Time: 10:13 AM
 */
public enum AlcyoneVector {
    UP(1),
    DOWN(-1);

    final int vector;
    AlcyoneVector(int vector) {
        this.vector=vector;
    }

    public int getMask() {
        return vector==-1?0:1;
    }
}
