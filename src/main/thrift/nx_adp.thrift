namespace java com.xiaoniuhy.adp.thrift
namespace py api.thrift

exception XNAdpException {
    1: i32 code;
    2: string reason;
}