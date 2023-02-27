module.exports = (content_type) => {
  return {
    'Content-Type': content_type,
    'Access-Control-Allow-Origin': '*'
  }
}