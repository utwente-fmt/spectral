/*
 * In the specification library we use `extern "C"` to force the specification 
 * functions to use the C calling convention. 
 * This simplifies the unification stage and ensures that the byval-attribute is 
 * present which helps with type-inference.
 * 
 * This is fine to use in this case, because the functions of the specification
 * library are only ever called from within the generated wrapper functions and
 * never e.g. from C-code. So even if types that are not FFI-safe are used, this
 * is not a problem.
 */


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
// TODO: Do we need [allow(improper-ctypes-definitions)]
#[inline(never)]
pub extern "C" fn _old<T>(_e: T) -> T { unimplemented!(); }

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


/* 
 *  Sequence ADTs
 */

 // The struct's first element is used to represent the content-type. 
 // The struct further contains a "randomly"-sized and unreasonably large array
 // to prevent it from being merged with a user's type and from optimized
 // by the compiler.
 #[allow(dead_code)]
 #[repr(C)]
 #[derive(Copy, Clone)]
pub struct _Seq<T> {
    pub c_type: T,
    pub dummy: [i32; 0x736571],
}

impl<T> _Seq<T> {
    #[inline(never)]
    pub extern "C" fn new() -> _Seq<T> { unimplemented!(); }

     #[inline(never)]
    pub extern "C" fn size(self) -> i64 { unimplemented!(); }

     #[inline(never)]
    pub extern "C" fn at(self, _idx: i64) -> T { unimplemented!(); }

    #[inline(never)]
    pub extern "C" fn prepend(self, _elem: T) -> _Seq<T> { unimplemented!(); }

    // TODO: Instead, use #[derive(PartialEq)] ?!
    #[inline(never)]
    pub extern "C" fn eq(self, _s2: _Seq<T>) -> bool { unimplemented!(); }

    #[inline(never)]
    pub extern "C" fn set(self, _idx: i64, _elem: T) -> _Seq<T> { unimplemented!(); }
    
    #[inline(never)]
    pub extern "C" fn slice(self, _from: i64, _to: i64) -> _Seq<T> { unimplemented!(); }

}

// TODO: Implement the full spec-lib