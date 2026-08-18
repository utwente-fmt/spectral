
/*
 *  Simple operators
 */

#[inline(never)]
// #[export_name = "_pallas_spec_imply"]
pub fn _imply(_a: bool, _b: bool) -> bool { unimplemented!(); }

#[inline(never)]
pub fn _and(_a: bool, _b: bool) -> bool { unimplemented!(); }

#[inline(never)]
pub fn _or(_a: bool, _b: bool) -> bool { unimplemented!(); }

#[inline(never)]
pub fn _sep(_a: bool, _b: bool) -> bool { unimplemented!(); }

/*
 *  Specification constructs
 */
#[inline(never)]
pub fn _old<T>(_e: T) -> T { unimplemented!(); }

#[inline(never)]
pub fn _result<T>() -> T { unimplemented!(); }

/*
 *  Quantifiers
 */
#[inline(never)]
pub fn _forall(_range: bool, _expr: bool) -> bool { unimplemented!(); }

#[inline(never)]
#[allow(non_snake_case)]
pub fn _forallS(_range: bool, _expr: bool) -> bool { unimplemented!(); }

#[inline(never)]
pub fn _exists(_range: bool, _expr: bool) -> bool { unimplemented!(); }

#[inline(never)]
pub fn _bv<T>(_id: &str) -> T { unimplemented!(); }

// TODO: Add the _inRange-macro!

/* 
 *  Permissions
 */

 // The struct contains a "randomly"-sized and unreasonably large array
 // to prevent it from being merged with a user's type and from optimized
 // by the compiler.
 #[allow(dead_code)]
 #[repr(C)]
 #[derive(Copy, Clone)]
pub struct Frac {
    pub dummy: [i32; 0x66726163],
}

impl Frac {
    #[inline(never)]
    pub fn of(_num: i32, _denom: i32) -> Frac { unimplemented!(); } 
}

// We make this an 'extern "C"' to simplify the unification-stage!
#[inline(never)]
#[allow(non_snake_case)]
pub extern "C" fn _Perm<T>(_loc: &T, _p: Frac) -> bool { unimplemented!(); }

// TODO: Do we need pointer_length etc?

/* 
 *  Predicates
 */
// TODO: Do we need #[allow(improper-ctypes-definitions)]
#[inline(never)]
pub extern "C" fn _unfolding<T>(_pred: bool, _in: T) -> T { unimplemented!(); }

// TODO: Add the sequence ADTs



// TODO: Implement the full spec-lib