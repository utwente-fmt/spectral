
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

 // Placeholders ensure that the struct is sufficiently large so that the 
 //     compiler does not attempt to deconstruct it for ABI compliance. 
 #[allow(dead_code)]
pub struct Frac {
    pub placeholder_1: i64,
    pub placeholder_2: i64,
    pub placeholder_3: i64,
    pub placeholder_4: i64,
    pub placeholder_5: i64
}

#[inline(never)]
pub fn _frac(_num: i32, _denom: i32) -> Frac { unimplemented!(); }

// TODO: What should the _perm function look like?
//       This is only a prototype
#[inline(never)]
#[allow(non_snake_case)]
pub fn _Perm<T>(_loc: &T, _p: Frac) -> bool { unimplemented!(); }

// TODO: Do we need pointer_length etc?

// TODO: Add the sequence ADTs



// TODO: Implement the full spec-lib